/*
 * A5.c
 */
#include "A5.h"

volatile uint16_t global_toggle;
volatile uint16_t data;

void timer_A_init(){
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CCIE;

    TIMER_A0->CCR[0] = 60000;
    TIMER_A0->CCR[1] = 30000; //15000

    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | // SMCLK
                    TIMER_A_CTL_MC_1;      // UP MODE

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);   // set NVIC interrupt
    NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);

    __enable_irq();     // Enable global interrupt
}

// Timer A0_0 interrupt service routine
void TA0_0_IRQHandler() {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  // Clear the CCR0 interrupt
    global_toggle = 1;
}

void TA0_N_IRQHandler() {
    TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG;  // Clear the CCR0 interrupt
    global_toggle = 0;
}
