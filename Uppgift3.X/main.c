/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator
'*/

#include <htc.h>

#define UP 1
#define DOWN 0

#define DS4 LATA5
#define DS5 LATA1
#define DS6 LATA2
#define DS7 LATC5

#define PULL_UPS

#define SWITCH PORTAbits.RA2

#define _XTAL_FREQ 500000

unsigned char _direction;
void interrupt IST(void);

void main(void)
{
    OSCCON = 0b00111000;    //set frequency as 500Hz
    TRISA = 0;
    TRISC = 0;              //set LED pins as output    
    LATC = 0;               //clear LED pins
    LATB = 0;
    LATA = 0;
    
    TRISCbits.TRISC4 = 1;   //set C4(Switch 1) as input
    
    DS6 = DS7 = 1;
    
    #ifdef PULL_UPS
        WPUC4 = 1;
        nWPUEN = 0;
    #endif    
    
    OPTION_REG = 0b00000111;
    INTCONbits.TMR0IE = 1;
    
    INTCONbits.IOCIE = 1;
    IOCCNbits.IOCCN4 = 1;
    GIE = 1;
    
    while (1) { continue; }
}

void interrupt ISR(void)
{
    if(IOCCF)
    {
        IOCCF = 0;
        __delay_ms(5);
        if(SWITCH == DOWN)
        {
            DS4 = DS5 = ~DS4;
            DS6 = DS7 = ~DS6;
        }
    }
    
    if(INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
    }
}