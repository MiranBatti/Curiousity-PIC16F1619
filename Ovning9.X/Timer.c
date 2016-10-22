/*
 * File:   Timer.c
 * Author: Miran
 *
 * Created on 18 May 2016, 18:44
 */


#include <htc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 500000
 
void main(void)
{
    OSCCON = 0b00111000;        //set frequency to 500Hz
    TRISC = 0;                  //set LED pins as output
    LATC = 0;                   //clear all LED pins
    
    OPTION_REG = 0b00000111;    //timer prescaler is 1:256
    
    LATCbits.LATC4 = 1;         //enable LED C4
    
    while(1)
    {
        while(!INTCONbits.TMR0IF) continue; //interrupt when overflow on timer0 has occurred
        
        INTCONbits.T0IF = 0;    //reset timer0
        LATC >> = 1;            //rotate to next LED
        
        if(STATUSbits.C)        //restart pattern
            LATCbits.LATC3 = 1; 
    }
    
}
