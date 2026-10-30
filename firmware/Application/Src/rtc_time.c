#include "rtc_time.h"

bool RTC_IsTimeSet(void)
{
    return HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0) == RTC_SET_MAGIC;
}

HAL_StatusTypeDef RTC_SetDateTime(uint8_t year, uint8_t month, uint8_t date,
                                  uint8_t weekday, uint8_t hours,
                                  uint8_t minutes, uint8_t seconds)
{
    RTC_TimeTypeDef t = {0};   // zero-init: DayLightSaving, StoreOperation, TimeFormat
    RTC_DateTypeDef d = {0};

    t.Hours   = hours;         // 0–23 (24h format)
    t.Minutes = minutes;
    t.Seconds = seconds;

    d.Year    = year;          // 0–99
    d.Month   = month;         // 1–12 (RTC_MONTH_xxx)
    d.Date    = date;          // 1–31
    d.WeekDay = weekday;       // 1–7 (RTC_WEEKDAY_MONDAY..SUNDAY), must not be 0

    if (HAL_RTC_SetTime(&hrtc, &t, RTC_FORMAT_BIN) != HAL_OK) return HAL_ERROR;
    if (HAL_RTC_SetDate(&hrtc, &d, RTC_FORMAT_BIN) != HAL_OK) return HAL_ERROR;

    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, RTC_SET_MAGIC);
    return HAL_OK;
}