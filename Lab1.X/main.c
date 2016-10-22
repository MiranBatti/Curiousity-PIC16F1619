/*
 * File:   main.c
 * Author: Miran
 *
 * Created on 06 May 2016, 20:02
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


void main(void)
    {
    char i;
    init();
    print_instr(CLEAR);
    i=0;
    for(;;)
        {
	print_instr(ADDRESS + 0);
        print_char(i/100+'0');
        print_char((i%100)/10+'0');
        print_char(i%10+'0');
        i++;
        __delay_ms(250);

        print_instr(ADDRESS + 0x40);
        print_char(' ');
        print_char('H');
        print_char('e');
        print_char('j');
        }
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