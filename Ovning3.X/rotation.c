/*
 * File:   rotation.c
 * Author: Miran Batti
 * Summary: This program diodes from the right to the left
 * Created on 24 April 2016, 16:49
 */


#include <htc.h>

#define _XTAL_FREQ 500000
//lysdioder                       
#define RC2_LED LATC2
#define RC3_LED LATC3
#define RC6_LED LATC6
#define RC7_LED LATC7

unsigned char rotateCounter = 1;

void main(void) {
    TRISC = 0b0010001; //sets pins as output
    OSCCON = 0b00111000; //clock speed 500kHz
    LATC = 0b0000000; //clear all PORT C pins
    
    while(1) {
        __delay_ms(500);            
        
        // Determine which LED will light up
        rotateCounter==1 ? RC2_LED = 1 : RC2_LED = 0; //if rotateIndex is 1: activate first diode, else: turn off diode.
        rotateCounter==2 ? RC3_LED = 1 : RC3_LED = 0; // etc. 
        rotateCounter==3 ? RC6_LED = 1 : RC6_LED = 0; 
        rotateCounter==4 ? RC7_LED = 1 : RC7_LED = 0; 
        
        rotateCounter++; //increment counter
                
        // If the last LED has been lit, restart the pattern
        if(rotateCounter == 5)                                                     
            rotateCounter = 1;
    }
}
