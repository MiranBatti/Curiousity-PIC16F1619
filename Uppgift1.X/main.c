/*
 * File:   main.c
 * Author: Miran
 *
 * Created on 29 May 2016, 12:03
 */


#include <htc.h>
//macros are defined here                                                                                                          
#define LED LATB
#define _XTAL_FREQ 500000

unsigned char ledArr[] = {0b00010000, 0b00100000, 0b01000000, 0b10000000}; //[1=RB4][2=RB5][3=RB6][3=RB7]
unsigned int counter = 0;
unsigned int endCounter = 0;

void main(void)
{
    OSCCON = 0b00111000;            //500KHz clock speed
    TRISB = 0b00001111;             //set RB4-7 as output
    
    LED = 0;                        //clear pin
    
    while(1)
    {
        __delay_ms(500);
        LED = ledArr[counter];       //rotate LED
        
        if(counter == 0)
            __delay_ms(5000);
        
        if(counter == 2)
            __delay_ms(10000);

        if(counter == 3)
            __delay_ms(1000);
        
        counter++;
        
        if(counter == 4)
        {
            counter = 0;
            endCounter++;
        }
        
        if(endCounter == 9)
        {
            LATB = 0;
            __delay_ms(5000);
        }    
    }
}