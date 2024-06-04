int main(void) {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    
    Init_GPIO();
    Init_Timer();
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
