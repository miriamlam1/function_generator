#include "P2.h"

void waveform_to_LCD(Waveform *wave){
    Clear_LCD();
    char freq[4];
    sprintf(freq, "%d", FREQ_6_MHZ/wave -> current_freq);
    char duty[4];
    sprintf(duty, "%d", wave -> duty * 10);

    switch(wave->waveform){
        case SINE:
            Write_word_LCD("SINE WAVE");    // Display type of waveform
            break;
        case SQUARE:
            Write_word_LCD("SQUARE WAVE ");
            Write_word_LCD(duty);
            Write_word_LCD("% duty");
            break;
        case SAWTOOTH:
            Write_word_LCD("SAWTOOTH WAVE");
            break;
    }
    line_LCD(2);               // Move to second line of LCD
    Write_word_LCD(freq);
    Write_word_LCD(" Hz");      // Display freq. of waveform
}

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
            if ((wave-> duty) > 1)
                wave-> duty -= 1;
            break;
        case BUTTON0: // resets duty
            wave-> duty = 5;
            break;
        case BUTTON_POUND: // increases duty
            if ((wave-> duty) < 9)
                wave-> duty += 1;
            break;
    }
    waveform_to_LCD(wave);
    TIMER_A0->CCR[0] = wave -> current_freq;
    TIMER_A0->CCR[1] = (wave -> current_freq)*(wave->duty)/10;
}

void make_waveform(Waveform *wave){
    switch(wave->waveform){
        case SQUARE:
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
