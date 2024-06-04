#include "fsl_i2c.h"
#include "MAG3110.h"

// Địa chỉ I2C của MAG3110
#define MAG3110_I2C_ADDRESS 0x1D

// Hàm khởi tạo MAG3110
void MAG3110_Init(void) {
    uint8_t data = 0x00;
    
    // Đặt chế độ standby
    I2C_WriteRegister(MAG3110_I2C_ADDRESS, MAG3110_CTRL_REG1, data);
    
    // Đặt giá trị oversample ratio
    data = 0x80;
    I2C_WriteRegister(MAG3110_I2C_ADDRESS, MAG3110_CTRL_REG1, data);
    
    // Đặt chế độ active
    data = 0x01;
    I2C_WriteRegister(MAG3110_I2C_ADDRESS, MAG3110_CTRL_REG1, data);
}

// Hàm đọc giá trị từ MAG3110
void MAG3110_Read(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[6];
    
    I2C_ReadRegisters(MAG3110_I2C_ADDRESS, MAG3110_OUT_X_MSB, data, 6);
    
    *x = ((int16_t)data[0] << 8) | data[1];
    *y = ((int16_t)data[2] << 8) | data[3];
    *z = ((int16_t)data[4] << 8) | data[5];
}
