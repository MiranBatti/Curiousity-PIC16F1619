/*
 * File:   main.c
 * Author: Miran
 *
 * Created on 16 April 2016, 10:30
 */


#include <htc.h>
#include "pin_manager.h" 
#define RA4_LED_TRIS TRISA4
#define RA4_LED_LAT LATA4
#define RA4_LED_Toggle()   do { LATA4 = ~LATA4; } while(0)
unsigned char counter = 0;

void main(void) {     
    RA4_LED_TRIS = 0;
    RA4_LED_LAT = ~RA4_LED_LAT;
    
        counter++;
        if(counter == 3){       
            RA4_LED_LAT = ~RA4_LED_LAT;  
            counter = 0;
        }
    
    while(1) continue;            
}