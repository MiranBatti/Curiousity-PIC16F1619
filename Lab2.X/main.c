/*
 * File:   main.c
 * Author: Miran
 *
 * Created on 15 May 2016, 18:42
 */

#include <stdio.h>
#include <stdlib.h>
#include <htc.h> 
#define _XTAL_FREQ 500000
 
#define E_bit PORTAbits.RA0
#define RS_bit PORTAbits.RA2
#define CLEAR 0x01
#define ADDRESS 0x80 

void init (void);
void init_display(void);
void print_char(char data);
void print_instr(char instr);
void print_text(const char *data);
void EE(void);
void E(void);
unsigned int adc(void);

unsigned char digits[5];
unsigned int adcval;

void main(void)
    {
      
    init();
    print_instr(CLEAR);
    
    TRISCbits.TRISC0 = 1;         //Potentiometer is connected to RC0...set as input
    ANSELCbits.ANSC0 = 1;         //analog
    ADCON1 = 0b11000000;     //right justified, Fosc/4, Vref- is VSS, Vref+ is VDD 
    ADCON0 = 0b01110101;   //select temp module 
    FVRCON = 0b01110000;
    
    while(1){
	    adcval = adc();             //grab the 10 bits
        
        int mV = adcval * 5000.0 / 1024.0;
        int celsius = mV/10.0;
        
        __delay_ms(5);             //delay for AT LEAST 5ms
        digits[0] = celsius / 1000 + 48;
        digits[1] = (celsius / 100) % 10 + 48;
        digits[2] = (celsius / 10) % 10 + 48;
        digits[3] = celsius % 10 + 48;
        digits[4] = '\0';

        //print_text(digits);
        print_instr(ADDRESS + 0);
        print_char(digits[0]);
        print_char(digits[1]);
        print_char(digits[2]);
        print_char(digits[3]);
        print_char(' ');
        print_char('C');
        __delay_ms(250);
        print_instr(ADDRESS + 0x40);
        print_char(' ');
        print_char('H');
        print_char('e');
        print_char('j');

        
        }
    }
    
unsigned int adc(void) {
    __delay_us(5);                //wait for ADC charging cap to settle
    GO = 1;
    while (GO) continue;          //wait for conversion to be finished

    return ((ADRESH << 8) | ADRESL);                
}


void init (void)
    {
    LATA=0;
    LATB=0;
    PORTA=0;
    PORTB=0;
    ANSELA=0;
    ANSELB=0;
    TRISA=0;
    TRISB=0;
    init_display();
    }
  


void init_display(void)
	{
		// See the datasheet flow chart for the procedure below
		// This part initiates the LCD in 4-bit mode...
        __delay_ms(25);
		PORTB=0x30;
		EE();
		PORTB=0x30;
		EE();
		PORTB=0x30;
		EE();
		PORTB=0x20;
		EE();
	
		// Set LCD properties...
		print_instr(0x28);	// 2: Dual line (even though it is single line)
		print_instr(0x0C);	// 3: Display on, cursor, blink
		print_instr(CLEAR);	// 4: Clear
		print_instr(0x06);	// 5: Entry mode set

// LCD is now initialized...
	}

/*******************************************/
// Print chars to LCD with 4-bit method
/*******************************************/
void print_char(char data)
	{
		//PORTC = (data >> 4) & 0x0F;
        PORTB = data & 0xF0;
		RS_bit=1; // RS
		E();

		//PORTC = data & 0x0F;
        PORTB = (data << 4) & 0xF0;
		RS_bit=1; // RS
		E();
        PORTB=0;
        PORTA=0;
	}

/*******************************************/
// Print instruction to LCD with 4-bit method
/*******************************************/
void print_instr(char instr)
	{
		//PORTC = (instr >> 4) & 0x0F;
        PORTB = instr & 0xF0;
		E();

		//PORTC = instr & 0x0F;
        PORTB = (instr << 4) & 0xF0;
		E();
        PORTB=0;
        PORTA=0;
	}

/*******************************************/
// Toggle E to execute command/instruction
// With a litle bit longer delay than std.
/*******************************************/
void EE(void)
	{
		__delay_ms(5);
		E_bit=0;
		__delay_ms(5);
		E_bit=1;
		__delay_ms(5);
		E_bit=0;
		__delay_ms(5);
	}

/*******************************************/
// Toggle E to execute command/instruction
/*******************************************/
void E(void)
	{
		__delay_us(25);
		E_bit=0;
		__delay_us(25);
		E_bit=1;
		__delay_us(25);
		E_bit=0;
		__delay_us(25);
	}

void print_text(const char *data)
    {
    char i=0;
    while(data[i])
        {
        print_char(data[i++]);
        }
    print_instr(ADDRESS+0x60);
    i=0;
    while(data[i]&&(i<8))
        {
        print_char(data[i++]);
        }
    if (i==8)
        {
        print_instr(ADDRESS+0x40);
        while(data[i])
            {
            print_char(data[i++]);
            }
        }

    }
