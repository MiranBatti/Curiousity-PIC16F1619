/*
 * File:   Debounce.c
 * Author: Miran
 *
 * Created on 07 May 2016, 15:32
 */
                         

#include <htc.h>

#define _XTAL_FREQ 500000
#define DOWN 0
#define UP 1
#define SWITCH PORTCbits.RC4
#define LED LATCbits.LATC2

void main(void) {
    OSCCON = 0b00111000;
    TRISC = 0b00010000;
    LATC = 0;
    
    while(1) {
        if(SWITCH == DOWN) {
            __delay_ms(10);
            LED = 1;
        } else
            LED = 0;
    }
}