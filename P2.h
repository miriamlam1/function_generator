#ifndef P2_H_
#define P2_H_

#include "msp.h"
#include "A7.h"
#include "A5.h"
#include "A4.h"

#define freq_100Hz 30000
#define freq_200Hz 15000
#define freq_300Hz 10000
#define freq_400Hz 7500
#define freq_500Hz 6000

void inc_duty_cycle10(uint16_t current_freq, uint16_t duty_freq);
void dec_duty_cycle10(uint16_t current_freq, uint16_t duty_freq);
void reset_duty_cycle(uint16_t current_freq);

#endif /* P2_H_ */
