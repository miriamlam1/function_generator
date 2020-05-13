#ifndef P2_H_
#define P2_H_

#include "msp.h"
#include "A7.h"
#include "A5.h"
#include "A4.h"

#define freq_50Hz 30000 // 20 ms
#define freq_100Hz 15000 // 10 ms
#define freq_200Hz 7500 // 5 ms
#define freq_300Hz 5000 // 3.333 ms
#define freq_400Hz 3750 // 2.5 ms
#define freq_500Hz 3000 // 2 ms

#define SQUARE 0
#define SAWTOOTH 1
#define SINE 2

typedef struct
{
   uint16_t current_freq;
   uint16_t duty_freq;
   uint8_t waveform;
} Waveform;

void make_waveform(Waveform *wave);
void waveform_vars(uint8_t button, Waveform *wave);

#endif /* P2_H_ */
