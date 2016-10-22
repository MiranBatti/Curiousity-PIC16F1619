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

#define LEFT 0
#define RIGHT 1

#define LED_LEFT 0
#define LED_RIGHT 1

#define PULL_UPS

#define SWITCH PORTAbits.RA2

#define _XTAL_FREQ 500000

unsigned char _direction;
void interrupt IST(void);

void main(void)
{
    OSCCON = 0b00111000;    //set frequency as 500Hz
    TRISC = 0;              //set LED pins as output    
    LATC = 0;               //clear LED pins
    
    LATCbits.LATC3 = 1;     //light first LED
    _direction = LED_RIGHT; //rotate from right to left
    
    TRISCbits.TRISC4 = 1;   //set C4(Switch 1) as input
    
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
            _direction ^= 1;
    }
    
    if(INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
    
        if(_direction == LED_RIGHT)
        {
            LATC >> = 1;
            if(STATUSbits.C == 1)
                LATCbits.LATC3 = 1;
        }
        else
        {
            LATC << = 1;
            if(LATCbits.LATC4 == 1)
                LATCbits.LATC0 = 1;
        }
    }
}