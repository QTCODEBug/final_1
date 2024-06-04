#include "fsl_pit.h"

// Hàm khởi tạo timer
void Init_Timer(void) {
    pit_config_t pitConfig;
    
    PIT_GetDefaultConfig(&pitConfig);
    PIT_Init(PIT, &pitConfig);
    
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(500000U, CLOCK_GetFreq(kCLOCK_BusClk)));
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    
    NVIC_EnableIRQ(PIT0_IRQn);
    PIT_StartTimer(PIT, kPIT_Chnl_0);
}

// ISR cho timer
void PIT0_IRQHandler(void) {
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    
    if (isSystemActive) {
        GPIO_TogglePinsOutput(GPIOB, 1U << LED_GREEN_PIN);
    } else {
        GPIO_TogglePinsOutput(GPIOE, 1U << LED_RED_PIN);
    }
}
