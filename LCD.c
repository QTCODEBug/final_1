#include "LCD.h"
#include "MKL46Z4.h"
#include <math.h>
#include <stdio.h>

// Các d?nh nghia cho các chân k?t n?i LCD
#define LCD_RS 1  // Register select pin
#define LCD_EN 2  // Enable pin
#define LCD_D4 3  // Data pin 4
#define LCD_D5 4  // Data pin 5
#define LCD_D6 5  // Data pin 6
#define LCD_D7 6  // Data pin 7

void delayMs(int n);
void pulseEnable(void);
void sendNibble(uint8_t nibble);
void sendByte(uint8_t byteToSend, uint8_t isData);

// Hàm kh?i t?o LCD
void LCD_Init(void) {
    // C?u hình các chân GPIO làm d?u ra
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    PORTB->PCR[LCD_RS] = PORT_PCR_MUX(1);
    PORTB->PCR[LCD_EN] = PORT_PCR_MUX(1);
    PORTB->PCR[LCD_D4] = PORT_PCR_MUX(1);
    PORTB->PCR[LCD_D5] = PORT_PCR_MUX(1);
    PORTB->PCR[LCD_D6] = PORT_PCR_MUX(1);
    PORTB->PCR[LCD_D7] = PORT_PCR_MUX(1);

    GPIOB->PDDR |= (1 << LCD_RS) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);

    delayMs(20);
    sendNibble(0x03);
    delayMs(5);
    sendNibble(0x03);
    delayMs(1);
    sendNibble(0x03);
    sendNibble(0x02);  // Chuy?n sang ch? d? 4-bit

    sendByte(0x28, 0); // 4-bit, 2 dòng, 5x8 di?m ?nh
    sendByte(0x08, 0); // T?t màn hình
    sendByte(0x01, 0); // Xóa màn hình
    sendByte(0x06, 0); // Chuy?n con tr? sang ph?i
    sendByte(0x0C, 0); // B?t màn hình, t?t con tr?
}

// Hàm xóa màn hình LCD
void LCD_Clear(void) {
    sendByte(0x01, 0);
    delayMs(2);
}

// Hàm d?t con tr? LCD
void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? 0x00 : 0x40;
    address += col;
    sendByte(0x80 | address, 0);
}

// Hàm ghi ký t? lên LCD
void LCD_WriteChar(char c) {
    sendByte(c, 1);
}

// Hàm ghi chu?i ký t? lên LCD
void LCD_WriteString(const char *str) {
    while (*str) {
        LCD_WriteChar(*str++);
    }
}

// Hàm hi?n th? hu?ng trên LCD
void Display_Direction(int16_t x, int16_t y) {
    char buffer[16];
    float direction;
    
    direction = atan2((double)y, (double)x) * 180 / 3.14159;
    if (direction < 0) {
        direction += 360;
    }
    
    sprintf(buffer, "Direction: %.2f", direction);
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_WriteString(buffer);
}

// Các hàm ph? tr?
void delayMs(int n) {
    int i;
    int j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 7000; j++) {}
}

void pulseEnable(void) {
    GPIOB->PSOR = (1 << LCD_EN);
    delayMs(1);
    GPIOB->PCOR = (1 << LCD_EN);
    delayMs(1);
}

void sendNibble(uint8_t nibble) {
    GPIOB->PCOR = (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);
    GPIOB->PSOR = ((nibble >> 0) & 0x01) << LCD_D4;
    GPIOB->PSOR = ((nibble >> 1) & 0x01) << LCD_D5;
    GPIOB->PSOR = ((nibble >> 2) & 0x01) << LCD_D6;
    GPIOB->PSOR = ((nibble >> 3) & 0x01) << LCD_D7;
    pulseEnable();
}

void sendByte(uint8_t byteToSend, uint8_t isData) {
    if (isData) {
        GPIOB->PSOR = (1 << LCD_RS);
    } else {
        GPIOB->PCOR = (1 << LCD_RS);
    }
    sendNibble(byteToSend >> 4);
    sendNibble(byteToSend & 0x0F);
}
