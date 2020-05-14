
#ifndef A5_H_
#define A5_H_
#include "msp.h"

extern volatile uint8_t global_toggle;
extern volatile uint16_t data;

void timer_A_init();
void PORT1_IRQHandler();
void TA0_0_IRQHandler();
void TA0_N_IRQHandler();

#endif /* A5_H_ */
