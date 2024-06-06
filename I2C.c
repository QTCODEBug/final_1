#include "I2C.h"
#include "MKL46Z4.h"

// Ð?nh nghia các thông s? c?a I2C
#define I2C_BAUDRATE 100000U
#define I2C0_CLK_SRC CLOCK_GetFreq(I2C0_CLK_SRC)

void I2C_Init(void) {
    // Kích hoat clock cho I2C0
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Cau hình chân I2C (SCL và SDA)
    PORTC->PCR[8] = PORT_PCR_MUX(2);
    PORTC->PCR[9] = PORT_PCR_MUX(2);

    // Ðat clock nguon cho I2C0
    I2C0->F = I2C_F_ICR(0x14) | I2C_F_MULT(0);
    I2C0->C1 = I2C_C1_IICEN_MASK;
}

void I2C_WriteRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data) {
    // G?i di?u ki?n b?t d?u
    I2C0->C1 |= I2C_C1_TX_MASK;
    I2C0->C1 |= I2C_C1_MST_MASK;

    // G?i d?a ch? thi?t b?
    I2C0->D = (deviceAddress << 1);
    while (!(I2C0->S & I2C_S_IICIF_MASK));
    I2C0->S |= I2C_S_IICIF_MASK;

    // G?i d?a ch? thanh ghi
    I2C0->D = registerAddress;
    while (!(I2C0->S & I2C_S_IICIF_MASK));
    I2C0->S |= I2C_S_IICIF_MASK;

    // G?i d? li?u
    I2C0->D = data;
    while (!(I2C0->S & I2C_S_IICIF_MASK));
    I2C0->S |= I2C_S_IICIF_MASK;

    // G?i di?u ki?n d?ng
    I2C0->C1 &= ~I2C_C1_MST_MASK;
    I2C0->C1 &= ~I2C_C1_TX_MASK;
}

void I2C_ReadRegisters(uint8_t deviceAddress, uint8_t registerAddress, uint8_t *data, uint8_t length) {
    // G?i di?u ki?n b?t d?u
    I2C0->C1 |= I2C_C1_TX_MASK;
    I2C0->C1 |= I2C_C1_MST_MASK;

    // G?i d?a ch? thi?t b? v?i bit ghi
    I2C0->D = (deviceAddress << 1);
    while (!(I2C0->S & I2C_S_IICIF_MASK));
    I2C0->S |= I2C_S_IICIF_MASK;

    // G?i d?a ch? thanh ghi
    I2C0->D = registerAddress;
    while (!(I2C0->S & I2C_S_IICIF_MASK));
    I2C0->S |= I2C_S_IICIF_MASK;

    // G?i di?u ki?n l?p l?i
    I2C0->C1 |= I2C_C1_RSTA_MASK;

    // G?i d?a ch? thi?t b? v?i bit d?c
    I2C0->D = (deviceAddress << 1) | 1;
    while (!(I2C0->S & I2C_S_IICIF_MASK));
    I2C0->S |= I2C_S_IICIF_MASK;

    // Chuy?n sang ch? d? d?c
    I2C0->C1 &= ~I2C_C1_TX_MASK;

    for (uint8_t i = 0; i < length; i++) {
        if (i == length - 1) {
            I2C0->C1 |= I2C_C1_TXAK_MASK;
        } else {
            I2C0->C1 &= ~I2C_C1_TXAK_MASK;
        }
        
        data[i] = I2C0->D;
        while (!(I2C0->S & I2C_S_IICIF_MASK));
        I2C0->S |= I2C_S_IICIF_MASK;
    }

    // G?i di?u ki?n d?ng
    I2C0->C1 &= ~I2C_C1_MST_MASK;
}
