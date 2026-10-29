#include "display_refresh_task.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "stm32g0xx_hal_gpio.h"
#include "stm32g0xx_hal_rtc.h"
#include "stm32g0xx_hal_spi.h"
#include "stm32g0xx_hal_tim.h"
#include <stdint.h>
#include <string.h>

/*
 * Segment bit mapping (bit 7 = dot, controlled by writeBuffer):
 *   bit 6 = g (middle)
 *   bit 5 = f (upper-left)
 *   bit 4 = e (lower-left)
 *   bit 3 = d (bottom)
 *   bit 2 = c (lower-right)
 *   bit 1 = b (upper-right)
 *   bit 0 = a (top)
 *
 * Adjust values below if physical segment wiring differs.
 */
static const uint8_t seg7NumLut[10] = {
    0x3F, /* 0: a b c d e f   */
    0x06, /* 1:   b c         */
    0x5B, /* 2: a b   d e   g */
    0x4F, /* 3: a b c d     g */
    0x66, /* 4:   b c     f g */
    0x6D, /* 5: a   c d   f g */
    0x7D, /* 6: a   c d e f g */
    0x07, /* 7: a b c         */
    0x7F, /* 8: a b c d e f g */
    0x6F, /* 9: a b c d   f g */
};

static const uint8_t seg7Dot = 0x80;

void startDisplayRefreshTask(void *argument)
{
    // Display Buffer
    uint8_t displayBuffer[DISPLAY_SIZE];

    RTC_TimeTypeDef currentTime;
    
    // Initial Display Data
    memset(displayBuffer, 0xFF, sizeof(displayBuffer));

    // Setting the load enable high for display data transfer
    HAL_GPIO_WritePin(DISPLAY_UPDATE_GPIO_Port, DISPLAY_UPDATE_Pin, GPIO_PIN_SET);

    // Starting the display data transmission via SPI DMA 
    HAL_SPI_Transmit_DMA(&hspi1, displayBuffer, sizeof(displayBuffer));

    // Task Loop
    for(;;)
    {
        // Waiting for the display data transmission to be complete
        osThreadFlagsWait(DISPLAY_DATA_TX_CPLT, osFlagsWaitAny, osWaitForever);

        // Display Update

        // Get the current time from the RTC
        HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BCD);

        uint8_t tensSeconds = currentTime.Seconds / 10U;
        uint8_t onesSeconds = currentTime.Seconds - tensSeconds;

        uint8_t tensMinutes = currentTime.Minutes / 10U;
        uint8_t onesMinutes = currentTime.Minutes - tensMinutes;

        uint8_t tensHours = currentTime.Hours / 10U;
        uint8_t onesHours = currentTime.Hours - tensHours;

        displayBuffer[0] = seg7NumLut[onesSeconds] & seg7Dot;
        displayBuffer[1] = seg7NumLut[tensSeconds];

        displayBuffer[2] = seg7NumLut[onesMinutes] & seg7Dot;
        displayBuffer[3] = seg7NumLut[tensMinutes];

        displayBuffer[4] = seg7NumLut[onesHours] & seg7Dot;
        displayBuffer[5] = seg7NumLut[tensHours];

        // Setting the load enable high for display data refresh
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);

        // Starting the display data refresh via SPI DMA
        HAL_SPI_Transmit_DMA(&hspi1, displayBuffer, sizeof(displayBuffer));
    }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    // Peripheral Check
    if(hspi->Instance == SPI1)
    {
        // Setting the load enable low for display data to be latched
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);

        // Set the OS flag to confirm the completion of dispaly data transmission
        osThreadFlagsSet(displayRefreshTaskHandle, DISPLAY_DATA_TX_CPLT);
    }
}