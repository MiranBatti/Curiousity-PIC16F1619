/*
 * File:   heart.c
 * Author: Miran
 *
 * Created on 26 May 2016, 14:17
 */


#include <htc.h>

#define SDA PORTBbits.RB4
#define SCL PORTBbits.RB7

void I2CWait(void);

void main(void) {
    OSCCONbits.SCS = 0x02; //set the SCS bits to select internal oscillator block
    OSCCONbits.IRCF = 0x0F; //set OSCCON IRCF
     BAUD1CONbits.BRG16=0;  //BRGH IS NOT VALID IN SYNCHRONOUS TRANSMISSION
     SPBRGH=0X00;
    SPBRGL=0X19;
      SLRCONC=0xff;    //Slew rate IS LIMITED
        ANSELC=0x00;   //Digital mode is selected
        
    SDA = SCL = 1;
    SSPCONbits.SSPM0=0;
    SSPCON1bits.SSPM1=0;
    SSPCON1bits.SSPM2=0;
    SSPCON1bits.SSPM3=1;    //selecting I2C master mode

    SSP1STATbits.SMP=1;    //SLEW RATE CONTROL
    SSP1STATbits.CKE=1;   //CLOCK EDGE SELECT BIT
    
    SPEN=1;
    ACKEN=1;
    SSPCON1=0X28;          //sync. serial port enable bit is set along with I2C mastermode
    SSPADD=0X27;           //calculated value
    GIE=1;
    PIE1=1;
    TXIE=1;
    SSP1CON2bits.SEN = 1;
    I2CWait();
    
}

void I2CWait(void)
{
    while ((SSPCON2 & 0x1F ) || ( SSPSTAT & 0x04 ) );

}
