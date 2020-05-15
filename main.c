#include "msp.h"
#include "A7.h"
#include "A5.h"
#include "A4.h"
#include "P2.h"

void main()
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    keypad_init();
    timer_A_init();
    DAC_init();
    sine_list_maker();

    Waveform wave = {.current_freq = freq_100Hz,
                     .duty = 5,
                     .waveform = SQUARE
    };

    uint8_t button;
    while(1){
        button = getKeyVal();           // poll for keypress
        if(button != NO_BUTTON_PRESS){  // key was pressed
            waveform_vars(button, &wave); // change wave vals from button
            while(getKeyVal()!=NO_BUTTON_PRESS){
                make_waveform(&wave); // wait for depress
            }
        }
        make_waveform(&wave);
    }
}
