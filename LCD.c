#include "fsl_lcd.h"

// Hàm khởi tạo LCD
void LCD_Init(void) {
    lcd_config_t lcdConfig;
    
    LCD_GetDefaultConfig(&lcdConfig);
    LCD_Init(LCD, &lcdConfig);
    
    LCD_StartDisplay(LCD);
}

// Hàm hiển thị hướng trên LCD
void Display_Direction(int16_t x, int16_t y) {
    char buffer[16];
    float direction;
    
    direction = atan2((double)y, (double)x) * 180 / 3.14159;
    if (direction < 0) {
        direction += 360;
    }
    
    sprintf(buffer, "Direction: %.2f", direction);
    LCD_WriteString(LCD, buffer);
}
