#include "display_refresh_task.h"
#include "cmsis_os2.h"
#include "stm32g0xx_hal_gpio.h"
#include "stm32g0xx_hal_spi.h"
#include "stm32g0xx_hal_tim.h"
#include <stdint.h>
#include <string.h>

void writeBuffer
    (const uint8_t *charBuffer, const uint8_t dotPos, uint8_t *displayBuffer, const uint32_t size);

static uint8_t charToDisplay(const uint8_t character);
static void counter(uint32_t count, uint8_t *displayBuffer);

void startDisplayRefreshTask(void *argument)
{
    uint8_t displayBuffer[DISPLAY_SIZE];
    memset(displayBuffer, 0xFF, sizeof(displayBuffer));

    uint32_t count = 0U;

    HAL_SPI_Transmit_DMA(&hspi1, displayBuffer, sizeof(displayBuffer));

    for(;;)
    {
        osThreadFlagsWait(DISPLAY_DATA_TX_CPLT, osFlagsWaitAny, osWaitForever);

        counter(count, displayBuffer);
        
        ++count;

        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);

        HAL_SPI_Transmit_DMA(&hspi1, displayBuffer, sizeof(displayBuffer));
    }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
        osThreadFlagsSet(displayRefreshTaskHandle, DISPLAY_DATA_TX_CPLT);
    }
}

void writeBuffer
    (const uint8_t *charBuffer, const uint8_t dotPos, uint8_t *displayBuffer, const uint32_t size)
{
    if(charBuffer == NULL || displayBuffer == NULL)
    {
        return;
    }

    for(uint32_t i = 0; i < size; i++)
    {
        displayBuffer[i] = charToDisplay(charBuffer[i]);
        displayBuffer[i] |= (uint8_t)(((dotPos >> i) & 0x01U) << 7U);
    }
}

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
static const uint8_t seg7_lut[10] = {
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

static uint8_t charToDisplay(const uint8_t character)
{
    if(character >= '0' && character <= '9')
    {
        return seg7_lut[character - '0'];
    }

    return 0;
}

static void counter(uint32_t count, uint8_t *displayBuffer)
{
    if(count > 999999U || displayBuffer == NULL)
    {
        return;
    }

    for(int32_t i = (int32_t)DISPLAY_SIZE - 1; i >= 0; i--)
    {
        displayBuffer[i] = seg7_lut[count % 10U];
        count /= 10U;
    }
}