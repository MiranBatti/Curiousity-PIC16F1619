/*
 * File:   Reversible.c
 * Author: Miran
 *
 * Created on 07 May 2016, 15:54
 */


#include <htc.h>

#define UP 1
#define DOWN 0
#define LED_RIGHT 1
#define LED_LEFT 0
#define SWITCH PORTCbits.RC4
#define SWITCH_UP 1
#define SWITCH_DOWN 0
#define _XTAL_FREQ 500000

unsigned char delay, direction;
unsigned char previous_state = SWITCH_UP;

unsigned char adc(void);
unsigned char check_switch(void);

void main(void) {
    OSCCON = 0b00111000;
    direction =  LED_RIGHT;
    TRISA = 0;
    LATA = 0b000100;
    TRISC = 0b00010001; //set switch and potentiometer as inputs
    ADCON0 = 0b00010001; //enable potentiometer (AN4)
    ADCON1 = 0b00010000; //left justified, FOSC/8
    
    while(1) {
        delay = adc();
        __delay_ms(5);
        while(delay-- != 0) 
            __delay_ms(2);
        if(check_switch())
            direction ^= 1;
        if(direction == LED_RIGHT)
            LATAbits.LATA2 = 1;
        else {
            LATA << = 1;
            if(LATAbits.LATA2 == 1)
                LATAbits.LATA0 = 1;
        }
    }
}

unsigned char check_switch(void) {
    if(SWITCH == SWITCH_UP) {
        __delay_ms(5);
        
        if(previous_state == SWITCH_DOWN && SWITCH == SWITCH_DOWN) {
            return 0;
        } else if(SWITCH == SWITCH_DOWN) {
            previous_state = SWITCH_DOWN;
            return 1;
        } else {
            previous_state = SWITCH_UP;
            return 0;
        }
    } else {
        previous_state = SWITCH_UP;
        return 0;
    }
}

//start conversion
unsigned char adc(void) {
    __delay_us(5);
    GO = 1;
    while(GO) continue;
    return ADRESH;
} 