#include "brightness_task.h"
#include "cmsis_os2.h"
#include "stm32g0xx_hal_tim.h"

static const uint32_t brightnessUpdateRate = 500U;
static const uint16_t maxBrightnessValue = 1000U;

void startBrightnessTask(void *argument)
{
    // Everything related to brightness will be handled here
    // Sampling the ADC for the ambient light intensity
    // Getting the the data from DMA stream
    // Applying a brightness curve
    // Settting the PWM duty cycle

    // For now the brightness will be constant 12.5%
    const uint16_t currentBrightness = 20U;
    const uint16_t buzzerDutyCycle = 1000U / 2U;

    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, maxBrightnessValue - currentBrightness);
    __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, buzzerDutyCycle);

    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

    uint8_t toggle = 1U;

    for(;;)
    {   
        /*
        if(toggle == 1U)
        {
            HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
            toggle = 0U;
        }
        else 
        {
            HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
            toggle = 1U;
        }
        */
        osDelay(brightnessUpdateRate);
    }
}