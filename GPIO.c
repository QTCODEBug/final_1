#include "GPIO.h"
#include "MKL46Z4.h"
#include "global.h"

// Khai báo bi?n toàn c?c
volatile bool isSystemActive = false;

void GPIO_Init(void) {
    // Kích ho?t clock cho PORTB, PORTE, và PORTC
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTC_MASK;

    // C?u hình chân LED làm GPIO
    PORTB->PCR[5] = PORT_PCR_MUX(1);
    GPIOB->PDDR |= (1 << 5); // LED xanh
    GPIOB->PCOR |= (1 << 5);

    PORTE->PCR[29] = PORT_PCR_MUX(1);
    GPIOE->PDDR |= (1 << 29); // LED d?
    GPIOE->PCOR |= (1 << 29);

    // C?u hình chân SW1 và SW2 làm GPIO v?i ng?t
    PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0xA); // SW1
    GPIOC->PDDR &= ~(1 << 3);
    PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0xA); // SW2
    GPIOC->PDDR &= ~(1 << 12);

    // Kích ho?t ng?t
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
}

void PORTC_PORTD_IRQHandler(void) {
    if (PORTC->ISFR & (1 << 3)) {
        PORTC->ISFR |= (1 << 3);
        isSystemActive = !isSystemActive;
    }
    if (PORTC->ISFR & (1 << 12)) {
        PORTC->ISFR |= (1 << 12);
        isSystemActive = false;
    }
}
