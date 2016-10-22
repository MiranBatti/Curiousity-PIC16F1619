/*
 * File:   ADC.c
 * Author: Miran
 *
 * Created on 27 April 2016, 20:23
 */


#include <htc.h>
#define _XTAL_FREQ 500000

void main(void) {
    OSCCON = 0b00111000; //500KHz clock speed
    TRISB = 0; //all LED pins are outputs
    LATB = 0; //reset LED pins
    
    TRISCbits.TRISC1 = 1; //Potentiometer is connected to RC0, sets RC0 as input
    ANSELCbits.ANSC1 = 1; //Sets RC0 as analog input
     
    ADCON0bits.CHS = 5; //AN4!!!...? Select AN4 which is connected RC0

    ADCON0bits.ADON = 1; //Turn on the ADC module
    
    ADCON1bits.ADCS = 8; //FOSC/8 speed
    //ADCON1 = 0b00010000;
    
    while(1) {
        __delay_us(5);
        ADCON0bits.GO_nDONE = 1; //Start the conversion
        while(ADCON0bits.GO_nDONE) continue;
        LATB = ADRESH; //assign the top 4 MSBs to LEDs connected to Port B
    }
}