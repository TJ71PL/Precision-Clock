#include "brightness_task.h"
#include "cmsis_os2.h"
#include "stm32g0xx_hal_tim.h"

static const uint32_t brightnessUpdateRate = 1000U;
static const uint16_t maxBrightnessValue = 1000U;

void startBrightnessTask(void *argument)
{
    // Everything related to brightness will be handled here
    // Sampling the ADC for the ambient light intensity
    // Getting the the data from DMA stream
    // Applying a brightness curve
    // Settting the PWM duty cycle

    // For now the brightness will be constant 12.5%
    const uint16_t currentBrightness = maxBrightnessValue - 25U;

    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, currentBrightness);

    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

    for(;;)
    {
        osDelay(brightnessUpdateRate);
    }
}