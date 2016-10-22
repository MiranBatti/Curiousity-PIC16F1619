/*
 * File:   main.c
 * Author: Miran
 *
 * Created on April 18, 2016, 8:16 PM
 */


#include <htc.h>

#define RC2_LED_LAT LATC2
#define RC3_LED_LAT LATC3
#define RC6_LED_LAT LATC6
#define RC7_LED_LAT LATC7
unsigned int counter;

void main(void) {
    TRISC = 0; // sätter portar som output
    
    RC2_LED_LAT = 1;
    
    RC3_LED_LAT = RC6_LED_LAT = RC7_LED_LAT = 0;
    
    while(1) continue;
}
