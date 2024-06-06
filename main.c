#include "MKL46Z4.h"
#include "MAG3110.h"
#include "GPIO.h"
#include "LCD.h"
#include "Timer.h"
#include "global.h"
#include <stdbool.h>
#include <stdint.h>

volatile bool isSystemActive = false; // Khai báo bi?n toàn c?c

int main(void) {
    // Initialize components
    GPIO_Init();
    Timer_Init();
    LCD_Init();
    MAG3110_Init();

    int16_t x, y, z;

    while (1) {
        if (isSystemActive) {
            MAG3110_Read(&x, &y, &z);
            Display_Direction(x, y);
        }
    }
}
