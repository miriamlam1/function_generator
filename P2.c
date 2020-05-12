#include "msp.h"

void inc_duty_cycle10(uint16_t current_freq, uint16_t duty_freq){
    duty_freq -= (current_freq/10);
    TIMER_A0->CCR[1] = duty_freq;
}

void dec_duty_cycle10(uint16_t current_freq, uint16_t duty_freq){
    duty_freq += (current_freq/10);
    TIMER_A0->CCR[1] = duty_freq;
}

void reset_duty_cycle(uint16_t current_freq){
    TIMER_A0->CCR[1] = (current_freq/2);
}
