#ifndef RTC_TIME_H

#define RTC_TIME_H

#include "main.h"
#include "stm32g0xx_hal_rtc.h"
#include "stm32g0xx_hal_rtc_ex.h"
#include "stdbool.h"

#define RTC_SET_MAGIC   0x32F2U

extern RTC_HandleTypeDef hrtc;

bool RTC_IsTimeSet(void);

HAL_StatusTypeDef RTC_SetDateTime(uint8_t year, uint8_t month, uint8_t date,
                                  uint8_t weekday, uint8_t hours,
                                  uint8_t minutes, uint8_t seconds);

#endif // RTC_TIME_H