#include "hdc1080.h"

hdc1080_error_t hdc1080_init()
{
    const uint8_t config[3];

    config[0] = HDC1080_CONFIG_REG;
    config[1] = 0x10;
    config[2] = 0x00;

    HAL_I

    HAL_I2C_Mem_Write(&hi2c2, HDC1080_DEVICE_ADDR, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
}