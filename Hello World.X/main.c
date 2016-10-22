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
void main(void) {     
    RA4_LED_TRIS = 0;
    RA4_LED_LAT = 1;
    
    while(1) continue;            
}
