#ifndef HDC1080_H
#define HDC1080_H

#include "main.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_i2c.h"

// Register addresses
#define HDC1080_TEMP_REG       0x00
#define HDC1080_HUMIDITY_REG   0x01
#define HDC1080_CONFIG_REG     0x02
#define HDC1080_MANUFACTURER_ID_REG 0xFE
#define HDC1080_DEVICE_ID_REG   0xFF

extern I2C_HandleTypeDef hi2c2;

#define HDC1080_DEVICE_ADDR 0x40

typedef struct
{
    uint32_t temperature;
    uint32_t humidity;
}   hdc1080_data_t;

typedef enum
{
    HDC1080_OK = 0;
} hdc1080_error_t;

hdc1080_error_t hdc1080_init(void);
hdc1080_error_t hdc1080_get_temperature(uint32_t *temperature);
hdc1080_error_t hdc1080_get_humidity(uint32_t *humidity);
hdc1080_error_t hdc1080_get_temperature_humidity(uint32_t *temperature, uint32_t *humidity);

#endif // HDC1080_H