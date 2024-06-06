#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_WriteChar(char c);
void LCD_WriteString(const char *str);
void Display_Direction(int16_t x, int16_t y);

#endif /* LCD_H_ */
