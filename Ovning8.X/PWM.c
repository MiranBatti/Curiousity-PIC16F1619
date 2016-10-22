/*
 * File:   PWM.c
 * Author: Miran
 *
 * Created on May 8, 2016, 4:35 PM
 */


#include <htc.h>

#define _XTAL_FREQ 500000

void main(void) {
    OSCCON = 0b00111000;
    TRISC5 = 0;
    
    TRISCbits.TRISC0 = 1;
    ANSELCbits.ANSC0 = 1;
    ADCON0 = 0b00010001;
    ADCON1 = 0b00010000;
    
    CCP1CON = 0x9C;
    CCPR1H = 0x7F;
    CCPR1L = 0xC0;
    CCPTMRSbits.CCP1TSEL = 0x0;
    
    T2CONbits.TMR2ON = 1;
    
    LATC5 = 0;
    LATA = 0;
    
    RC5PPS = 0b00001100;
    
    while(1) {
       __delay_us(5);
       GO = 1;
       while(GO) continue;
       CCPR1H = ADRESH;
       CCPR1L = ADRESL;
    }
}