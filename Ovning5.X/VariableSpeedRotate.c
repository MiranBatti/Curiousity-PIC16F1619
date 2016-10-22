/*
 * File:   Variable Rotate Speed.c
 * Author: Miran Batti
 *
 * Created on 01 May 2016, 17:43
 */

#include <htc.h> 
#define _XTAL_FREQ 500000
unsigned char ledArr[] = {0b00000100, 0b00001000, 0b01000000, 0b10000000};
unsigned int counter = 0;
unsigned char adc(void);          //prototype

void main(void) {
    unsigned char delay = 0;

    OSCCON = 0b00111000; 
    TRISC = 0;                                                                         
    LATC = 0b11001100;             //start the rotation by setting RA2 ON - rotate from the right to left

    TRISCbits.TRISC0 = 1;         //Potentiometer is connected to RC0...set as input
    ANSELCbits.ANSC0 = 1;         //analog
    ADCON0 = 0b00010001;          //select RC0 as source of ADC and enable the module (AN4)
    ADCON1 = 0b00010000;          //left justified - FOSC/8 speed - Vref is Vdd


    while (1) {
       delay = adc();             //grab the top 8 MSbs
       __delay_ms(5);             //delay for AT LEAST 5ms
       while (delay-- != 0) 
       __delay_ms(2);             //decrement the 8 MSbs of the ADC and dealy 2ms for each
       LATC = ledArr[counter]; 
       counter++;
       if(counter == 4)                            
           counter = 0;
    }
}
unsigned char adc(void) {
    __delay_us(5);                //wait for ADC charging cap to settle
    GO = 1;
    while (GO) continue;          //wait for conversion to be finished

    return ADRESH;                //grab the top 8 MSbs
}
