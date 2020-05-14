#ifndef P2_H_
#define P2_H_

#include "msp.h"
#include "A7.h"
#include "A5.h"
#include "A4.h"

/* equation to determine frequencies:
 * 3,000,000/desiredfreq = CCR value
 */
#define freq_100Hz 30000 // 10 ms
#define freq_200Hz 15000 // 5 ms
#define freq_300Hz 10000 // 3.333 ms
#define freq_400Hz 7500 // 2.5 ms
#define freq_500Hz 6000 // 2 ms

#define SQUARE 0
#define SAWTOOTH 1
#define SINE 2

typedef struct
{
   uint16_t current_freq; // frequency that is #def as ccr value
   uint8_t waveform; // waveform type: sq, saw, sine
   float duty; // duty % as a value from .1-.9
} Waveform;

void make_waveform(Waveform *wave);
void waveform_vars(uint8_t button, Waveform *wave);

#endif /* P2_H_ */
