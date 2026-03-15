#ifndef HDC1080_H
#define HDC1080_H

// Register addresses
#define HDC1080_TEMP_REG       0x00
#define HDC1080_HUMIDITY_REG   0x01
#define HDC1080_CONFIG_REG     0x02
#define HDC1080_MANUFACTURER_ID_REG 0xFE
#define HDC1080_DEVICE_ID_REG   0xFF

// Low level I2C communication functions
bool i2cWrite(uint8_t deviceAddress, uint8_t registerAddress, uint8_t *data, size_t length);
bool i2cRead(uint_t deviceAddress, uint8_t registerAddress, uint8_t *data, size_t length);


void HDC1080_Init(void);


#endif // HDC1080_H