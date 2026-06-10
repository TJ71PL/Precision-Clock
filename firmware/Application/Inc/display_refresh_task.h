#ifndef DISPLAY_REFRESH_TASK_H

#define DISPLAY_REFRESH_TASK_H

#include "cmsis_os.h"
#include "main.h"
#include "stm32g0xx_hal_spi.h"
#include "stm32g0xx_hal_tim.h"

#define DISPLAY_SIZE            (uint32_t)6U

#define DISPLAY_DATA_TX_CPLT    (uint32_t)0x00000001

extern SPI_HandleTypeDef hspi1;

extern osThreadId_t displayRefreshTaskHandle;

void startDisplayRefreshTask(void *argument);

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);

#endif // DISPLAY_REFRESH_TASK_H
