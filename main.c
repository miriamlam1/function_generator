#include "msp.h"
#include "A7.h"
#include "A5.h"
#include "A4.h"
#include "P2.h"

/*void sawtooth(){

}*/

void main()
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    //keypad_init();
    timer_A_init();
    DAC_init();
    square();

    uint16_t current_freq = freq_100Hz;
    uint16_t duty_freq = freq_200Hz;

    while (1){
        uint8_t button = get_keypress();
        switch(button){
            case BUTTON1:
                current_freq = freq_100Hz;
                break;
            case BUTTON2:
                current_freq = freq_200Hz;
                break;
            case BUTTON3:
                current_freq = freq_300Hz;
                break;
            case BUTTON4:
                current_freq = freq_400Hz;
                break;
            case BUTTON5:
                current_freq = freq_500Hz;
                break;
            case BUTTON7:
                square();
                break;
            /*case BUTTON8:
                sine();
                break;
            case BUTTON9:
                sawtooth();
                break;*/
            case BUTTON_STAR:
                inc_duty_cycle10(current_freq,duty_freq);
                break;
            case BUTTON0:
                reset_duty_cycle(current_freq);
                break;
            case BUTTON_POUND:
                dec_duty_cycle10(current_freq,duty_freq);
                break;
        }
        TIMER_A0->CCR[0] = current_freq;
        TIMER_A0->CCR[1] = duty_freq;
    }
}
