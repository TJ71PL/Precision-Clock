#ifndef DISPLAY_REFRESH_TASK_H

#define DISPLAY_REFRESH_TASK_H

#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "main.h"
#include "stm32g0xx_hal_spi.h"
#include "stm32g0xx_hal_tim.h"
#include "stm32g0xx_hal_gpio.h"
#include "stm32g0xx_hal_rtc.h"
#include "stm32g0xx_hal_rtc_ex.h"
#include <stdint.h>
#include <string.h>
#include "rtc_time.h"

#define DISPLAY_SIZE            (uint32_t)6U

#define DISPLAY_DATA_TX_CPLT    (uint32_t)0x00000001

extern SPI_HandleTypeDef hspi1;

extern RTC_HandleTypeDef hrtc;

extern osThreadId_t displayRefreshTaskHandle;

void startDisplayRefreshTask(void *argument);

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);

#endif // DISPLAY_REFRESH_TASK_H
