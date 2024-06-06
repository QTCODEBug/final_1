#include "GPIO.h"
#include "MKL46Z4.h"
#include "global.h"

// Khai b�o bi?n to�n c?c
volatile bool isSystemActive = false;

void GPIO_Init(void) {
    // K�ch ho?t clock cho PORTB, PORTE, v� PORTC
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTC_MASK;

    // C?u h�nh ch�n LED l�m GPIO
    PORTB->PCR[5] = PORT_PCR_MUX(1);
    GPIOB->PDDR |= (1 << 5); // LED xanh
    GPIOB->PCOR |= (1 << 5);

    PORTE->PCR[29] = PORT_PCR_MUX(1);
    GPIOE->PDDR |= (1 << 29); // LED d?
    GPIOE->PCOR |= (1 << 29);

    // C?u h�nh ch�n SW1 v� SW2 l�m GPIO v?i ng?t
    PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0xA); // SW1
    GPIOC->PDDR &= ~(1 << 3);
    PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_IRQC(0xA); // SW2
    GPIOC->PDDR &= ~(1 << 12);

    // K�ch ho?t ng?t
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
