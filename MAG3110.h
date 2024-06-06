#ifndef MAG3110_H_
#define MAG3110_H_

#include <stdint.h>

// Ðia chi I2C cua MAG3110
#define MAG3110_I2C_ADDRESS 0x1D

// Ðia chi các thanh ghi cua MAG3110
#define MAG3110_OUT_X_MSB      0x01
#define MAG3110_OUT_X_LSB      0x02
#define MAG3110_OUT_Y_MSB      0x03
#define MAG3110_OUT_Y_LSB      0x04
#define MAG3110_OUT_Z_MSB      0x05
#define MAG3110_OUT_Z_LSB      0x06
#define MAG3110_CTRL_REG1      0x10
#define MAG3110_CTRL_REG2      0x11

// Khai báo các hàm
void MAG3110_Init(void);
void MAG3110_Read(int16_t *x, int16_t *y, int16_t *z);

#endif /* MAG3110_H_ */
