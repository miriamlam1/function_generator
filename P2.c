#include "msp.h"
#include "P2.h"

void waveform_vars(uint8_t button, Waveform *wave){
    switch(button){
        case BUTTON1:
            wave-> current_freq = freq_100Hz;
            break;
        case BUTTON2:
            wave-> current_freq = freq_200Hz;
            break;
        case BUTTON3:
            wave-> current_freq = freq_300Hz;
            break;
        case BUTTON4:
            wave-> current_freq = freq_400Hz;
            break;
        case BUTTON5:
            wave-> current_freq = freq_500Hz;
            break;
        case BUTTON7:
            wave-> waveform = SQUARE;
            break;
        case BUTTON8:
            wave-> waveform = SINE;
            break;
        case BUTTON9:
            wave-> waveform = SAWTOOTH;
            break;
        case BUTTON_STAR:
            wave -> duty_freq -= (wave -> current_freq/10);
            break;
        case BUTTON0:
            wave -> duty_freq = (wave -> current_freq*2);
            break;
        case BUTTON_POUND:
            wave -> duty_freq += (wave -> current_freq/10);
            break;
    }
}

void make_waveform(Waveform *wave){
    TIMER_A0->CCR[0] = wave -> current_freq;
    switch(wave->waveform){
        case SQUARE:
            TIMER_A0->CCR[1] = wave -> duty_freq;
            square();
            break;
        case SAWTOOTH:
            sawtooth(wave -> current_freq);
            break;
        case SINE:
            sine(wave->current_freq);
            break;
    }
}
