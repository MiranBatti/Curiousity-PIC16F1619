/**
  Author:
    Miran Batti

  File Name:
    helloworld.c

  Summary:
    This program activates diodes on pins RC2, RC3, RC6, RC7, and on-board leds,
*/

#include "mcc_generated_files/mcc.h"
#include <htc.h>

/*
    Main application
 */
void main(void)
{
    TRISA = 0b011001; //s�tter pins anslutna till lamporna p� mcu till output
    TRISC = 0b0010001; //s�tter pins som output
    
    LATA = 0b000000; //nollst�ller alla pins
    LATC = 0b0000000;
    
    while (1)
    {
        LATA = 0b00100110; //lyser lampor
        LATC = 0b00100000;
    };
}
/**
 End of File
*/