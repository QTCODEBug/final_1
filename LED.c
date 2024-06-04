#include "fsl_gpio.h"
#include "board.h"

// Định nghĩa chân cho LED và nút nhấn
#define LED_GREEN_PIN 5U
#define LED_RED_PIN 29U
#define SW1_PIN 3U
#define SW2_PIN 12U

// Trạng thái hệ thống
volatile bool isSystemActive = false;

// ISR cho nút nhấn SW1
void SW1_IRQHandler(void) {
    GPIO_ClearPinsInterruptFlags(GPIOC, 1U << SW1_PIN);
    isSystemActive = !isSystemActive;
}

// ISR cho nút nhấn SW2
void SW2_IRQHandler(void) {
    GPIO_ClearPinsInterruptFlags(GPIOC, 1U << SW2_PIN);
    isSystemActive = false;
}

// Hàm khởi tạo LED và nút nhấn
void Init_GPIO(void) {
    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
    gpio_pin_config_t sw_config = {kGPIO_DigitalInput, 0, kGPIO_IntFallingEdge};
    
    // Cấu hình LED
    GPIO_PinInit(GPIOB, LED_GREEN_PIN, &led_config);
    GPIO_PinInit(GPIOE, LED_RED_PIN, &led_config);
    
    // Cấu hình nút nhấn
    GPIO_PinInit(GPIOC, SW1_PIN, &sw_config);
    GPIO_PinInit(GPIOC, SW2_PIN, &sw_config);
    
    // Kích hoạt ngắt cho nút nhấn
    GPIO_PortEnableInterrupts(GPIOC, 1U << SW1_PIN);
    GPIO_PortEnableInterrupts(GPIOC, 1U << SW2_PIN);
    NVIC_EnableIRQ(PORTC_IRQn);
}
