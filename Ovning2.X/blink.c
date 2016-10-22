/*
 * File:   blink.c
 * Author: Miran Batti
 * 
 * Summary: This program flashes on-board led:s and diodes with a 40 second interval
 *
 * Created on 20 April 2016, 20:30
 */


#include <htc.h>

//lysdioder                       
#define RC2_LED LATC2
#define RC3_LED LATC3
#define RC6_LED LATC6
#define RC7_LED LATC7

//lampor på mcu
#define RA5_LED LATA5
#define RA2_LED LATA2
#define RA1_LED LATA1
#define RC5_LED LATC5

unsigned int delay;

void Delay(void);

void main(void) {
    //setup
    OSCCON = 0b00010000; //31.25KHz clock speed
    TRISC = 0b0010001; //sätter pins som output
    TRISA = 0b011001; //sätter pins till output
    RC2_LED = RC3_LED = RC6_LED = RC7_LED = 0; //nollställer lysdioder
    RA5_LED = RA2_LED = RA1_LED = RC5_LED = 0; //nollställer lamporna på mcu
    delay = 1000; //delay i ms (= 1 sek)

    //main loop
    while (1) {
        Delay();
        RC2_LED = RC3_LED = RC6_LED = RC7_LED = ~RC7_LED; //toggle lysdioder
        RA5_LED = RA2_LED = RA1_LED = RC5_LED = ~RC5_LED; //toggle lampor på mcu
        delay = 40000; //delay i ms (=40 sek)
    }
}

void Delay(void) {
    while (delay-- != 0)continue; //each instruction is ~1ms (1/(31.25KHz/4))
}