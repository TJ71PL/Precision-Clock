#ifndef BRIGHTNESS_TASK_H

#define BRIGHTNESS_TASK_H

#include "cmsis_os2.h"
#include "main.h"
#include "stm32g0xx_hal_tim.h"

extern osThreadId_t brightnessTaskHandle;

extern TIM_HandleTypeDef htim4;

void startBrightnessTask(void *argument);

#endif // BRIGHTNESS_TASK_H