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
        case BUTTON_STAR: // decreasing duty
            if ((wave-> duty) > .1)
                wave-> duty -= .1;
            break;
        case BUTTON0: // resets duty
            wave-> duty = .5;
            break;
        case BUTTON_POUND: // increases duty
            if ((wave-> duty) < .9)
                wave-> duty += .1;
            break;
    }
    TIMER_A0->CCR[0] = wave -> current_freq;
    TIMER_A0->CCR[1] = (wave -> current_freq) * (1-(wave -> duty));
}

void make_waveform(Waveform *wave){
    switch(wave->waveform){
        case SQUARE:
            square();
            break;
        case SAWTOOTH:
            //wave-> duty = .5;
            sawtooth(wave -> current_freq);
            break;
        case SINE:
            //wave-> duty = .5;
            sine(wave->current_freq);
            break;
    }
}
