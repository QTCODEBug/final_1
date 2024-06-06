#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

// Hàm khoi tao I2C
void I2C_Init(void);

// Hàm ghi mot byte vào mot thanh ghi cua thiet biI2C
void I2C_WriteRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data);

// Hàm dc byyyte I2C
void I2C_ReadRegisters(uint8_t deviceAddress, uint8_t registerAddress, uint8_t *data, uint8_t length);

#endif /* I2C_H_ */
