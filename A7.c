/* a7.c: DAC converter
    UCB0SIMO = P1.6
    UCB0CLK = P1.5
P4.1*/
#include <math.h>
#include "msp.h"
#include "A7.h"
#include "A5.h"
#include "P2.h"

volatile uint16_t volts_list[SINETABLESIZE];

void sawtooth(uint16_t current_freq){
    data = (TIMER_A0->R * THREEV) / current_freq;
    sendto_DAC(data);
}

void sine(uint16_t current_freq){
    data = (TIMER_A0->R)/current_freq;
    sendto_DAC(volts_list[data]);
}

// creates table of all values
void sine_list_maker(){
    int i;
    int voltage;
    for(i = 0; i < SINETABLESIZE; i++)
    {
        voltage = ONEHALFV * sin((i * 2 * M_PI)/ SINETABLESIZE) + ONEHALFV;
        volts_list[i] = voltage;
    }
}

// generates a 2vpp square wave 20 ms period 1v offset
void square(){
    if (global_toggle == 0){
        sendto_DAC(0);
    } else {
        sendto_DAC(THREEV);
    }
}

void triangle(){
    if (global_toggle == 0){ //direction up
        data = (TIMER_A0->R * 2482) / 30000;
        sendto_DAC(data);
    } else {
        data = 2482 - ((TIMER_A0->R * 2482) / 30000);
        sendto_DAC(data);
    }
}

void DAC_init(){
    P4->SEL0 &= ~NOTCS; // pin 4.1 GPIO
    P4->SEL1 &= ~NOTCS;
    P4->OUT |= NOTCS;   //initialize high bec CS is active low
    P4->DIR |= NOTCS;   // pin 4.1 is output

    P1->SEL0 |= (MOSI|SCLK);
    P1->SEL1 &= ~(MOSI|SCLK); // set to primary mode (SPI)

    EUSCI_B0 -> CTLW0 |= (EUSCI_B_CTLW0_SWRST | // software reset enabled
            EUSCI_B_CTLW0_MST | // master mode
            EUSCI_B_CTLW0_SYNC| // MSB first when transmitting
            EUSCI_B_CTLW0_MSB | // synchronous mode
            EUSCI_B_CTLW0_CKPL| // polarity: inactive state is high
            EUSCI_B_CTLW0_UCSSEL_2); // clock source: SMCLK

    //EUSCI_B0->BRW = 0x02;              // div by 2 fBitClock = fBRCLK / UCBRx
    EUSCI_B0 -> CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // software reset disabled
}

void sendto_DAC(uint16_t data){
    uint8_t top8 = 0x0F & (data >> 8);
    uint8_t lower8 = data & 0xFF;
    top8 |= (GAIN | SHDN);
    P4->OUT &= ~(NOTCS); //set CS bit low
    while (EUSCI_B0 -> IFG & EUSCI_B_IFG_TXIFG == 0);  //wait
    EUSCI_B0 -> TXBUF = top8; //transmit top8
    while (EUSCI_B0 -> IFG & EUSCI_B_IFG_TXIFG == 0);  //wait
    EUSCI_B0 -> TXBUF = lower8;
    while(EUSCI_B0 -> IFG & EUSCI_B_IFG_RXIFG == 0); //RXIFG is set when UCxxRXBUF has received a complete character
    P4->OUT |= (NOTCS); //set CS bit high
}
