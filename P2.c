#include "msp.h"
#include "P2.h"

void waveform_vars(uint8_t button, Waveform *wave){
    switch(button){
        case BUTTON1:
            wave-> current_freq = freq_50Hz;
            wave-> duty_freq = freq_100Hz;
            break;
        case BUTTON2:
            wave-> current_freq = freq_100Hz;
            wave-> duty_freq = freq_200Hz;
            break;
        case BUTTON3:
            wave-> current_freq = freq_150Hz;
            wave-> duty_freq = freq_300Hz;
            break;
        case BUTTON4:
            wave-> current_freq = freq_200Hz;
            wave-> duty_freq = freq_400Hz;
            break;
        case BUTTON5:
            wave-> current_freq = freq_250Hz;
            wave-> duty_freq = freq_500Hz;
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
            //if (wave -> current_freq > 9*(wave-> duty_freq)/10)
                wave -> current_freq -= (wave -> duty_freq/10); //dec duty
            break;
        case BUTTON0:
            wave -> current_freq = (wave -> duty_freq*2); //reset duty to 50%
            break;
        case BUTTON_POUND:
            //if (wave-> current_freq < (wave->duty_freq)/10)
                wave -> current_freq += (wave -> duty_freq/10); //inc duty
            break;
    }
}

void make_waveform(Waveform *wave){
    TIMER_A0->CCR[0] = wave -> current_freq;
    switch(wave->waveform){
        case SQUARE:
            TIMER_A0->CCTL[1] = TIMER_A_CCTLN_CCIE; // turn intr1 on
            TIMER_A0->CCR[1] = wave -> duty_freq;
            square();
            break;
        case SAWTOOTH:
            TIMER_A0->CCTL[1] = ~TIMER_A_CCTLN_CCIE; //turn intr1 off
            sawtooth(wave -> current_freq);
            break;
        case SINE:
            TIMER_A0->CCTL[1] = ~TIMER_A_CCTLN_CCIE; //turn intr1 off
            sine(wave->duty_freq);
            break;
    }
}
