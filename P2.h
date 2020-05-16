#ifndef P2_H_
#define P2_H_

#include "msp.h"
#include "A7.h"
#include "A5.h"
#include "A4.h"
#include "A3.h"
#include <stdio.h>

/* equation to determine frequencies:
 * 6,000,000/desiredfreq = CCR value
 */
#define FREQ_6_MHZ 6000000
#define freq_100Hz 60000 // 10 ms
#define freq_200Hz 30000 // 5 ms
#define freq_300Hz 20000 // 3.333 ms
#define freq_400Hz 15000 // 2.5 ms
#define freq_500Hz 12000 // 2 ms

#define SQUARE 0
#define SAWTOOTH 1
#define SINE 2

typedef struct
{
   uint16_t current_freq; // frequency that is #def as ccr value
   uint8_t waveform; // waveform type: sq, saw, sine
   uint8_t duty; // duty % as a value from .1-.9
} Waveform;

void waveform_to_LCD(Waveform *wave);
void make_waveform(Waveform *wave);
void waveform_vars(uint8_t button, Waveform *wave);

#endif /* P2_H_ */
