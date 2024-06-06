#include "Timer.h"
#include "MKL46Z4.h"
#include "GPIO.h"
#include "global.h"

void Timer_Init(void) {
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; // Enable clock for PIT
    PIT->MCR = 0x00; // Enable PIT module

    PIT->CHANNEL[0].LDVAL = 20971520; // Load value for 1 Hz blink rate
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK; // Enable timer interrupts
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK; // Start timer

    NVIC_EnableIRQ(PIT_IRQn); // Enable PIT interrupt in NVIC
}

void PIT_IRQHandler(void) {
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; // Clear interrupt flag
    
    if (isSystemActive) {
        GPIOB->PTOR |= (1 << 5); // Toggle green LED
    } else {
        GPIOE->PTOR |= (1 << 29); // Toggle red LED
    }
}
