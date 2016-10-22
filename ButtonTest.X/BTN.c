/*
 * File:   BTN.c
 * Author: Miran
 *
 * Created on May 1, 2016, 8:29 PM
 */


#include <htc.h>
#define _XTAL_FREQ 500000
unsigned char rotateCounter = 0;
unsigned char ledArr[] = {0b00000100, 0b00001000, 0b01000000, 0b10000000};
unsigned char adc(void);

void main(void) {
    TRISC = 0b0010001; //sets pins as output
    TRISB = 0;
    OSCCON = 0b00111000; //clock speed 500kHz
    LATC = 0b0000000; //clear all PORT C pins
    
    TRISBbits.TRISB4 = 1; //Potentiometer is connected to RC0, sets RC0 as input
    ANSELBbits.ANSB4 = 1; //Sets RC0 as analog input
     
    ADCON0bits.CHS = 10; //AN4!!!...? Select AN4 which is connected RC0

    ADCON0bits.ADON = 1; //Turn on the ADC module
    
    ADCON1bits.ADCS = 8; //FOSC/8 speed
    
    while(1) {
        __delay_ms(500);            
        
        LATC = ledArr[rotateCounter];
                
        rotateCounter = adc();

                
        // If the last LED has been lit, restart the pattern
        if(rotateCounter == 4)                                                     
            rotateCounter = 0;
    }
    
}

unsigned char adc(void) {
    __delay_us(5);                //wait for ADC charging cap to settle
    GO_nDONE = 1;
    while (GO_nDONE) continue;          //wait for conversion to be finished

    return ADRESH;                //grab the top 8 MSbs
}    