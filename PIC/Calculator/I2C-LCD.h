// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>  
#define _XTAL_FREQ 20000000  // Define your oscillator frequency, change according to your setup

void I2C_init();
void I2C_wait();
void I2C_start();
void I2C_stop();
void I2C_write(unsigned d);

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);

void I2C_init()
{
    SSPCON  = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD  = 0x3F;//address-reg---100kHz
    TRISC3  = 1;//i/p        
    TRISC4  = 1;//i/p
}

void I2C_wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));//(0x04)0000 0100--(0x1f)0001 0000  
}

void I2C_start()
{
    I2C_wait();
    SEN = 1;//start-condition-on-SDA&SCL-pin
}

void I2C_stop()
{
    I2C_wait();
    PEN = 1;//stop-condition-on-SDA&SCL-pin
}

void I2C_write(unsigned d)
{
    I2C_wait();
    SSPBUF = d;
    while(SSPIF==0);
    SSPIF=0;
}

void lcd_init()
{
    cmd(0x02);
    cmd(0x28);// 4-bit mode, 2 lines, 5x7 font
    cmd(0x06);
    cmd(0x0C);// Display ON, Cursor OFF, Blink OFF
    cmd(0x01);
    cmd(0x80);
}

void cmd(unsigned char a)
{
    unsigned char data_l, data_u;
    data_l = (a<<4) & 0xf0;  //select lower nibble by moving it to the upper nibble position
    data_u = a & 0xf0;  //select upper nibble

    I2C_start();
    I2C_write (0x4E);
    I2C_write (data_u|0x0C);  //enable=1 and rs =0
    I2C_write (data_u|0x08);  //enable=0 and rs =0

    I2C_write (data_l|0x0C);  //enable =1 and rs =0
    I2C_write (data_l|0x08);  //enable=0 and rs =0
    I2C_stop();
}

void dat (unsigned char b)
{
    unsigned char data_l, data_u;
    data_l = (b<<4) & 0xf0;  //select lower nibble by moving it to the upper nibble position
    data_u = b & 0xf0;  //select upper nibble

    I2C_start();
    I2C_write (0x4E);
    I2C_write (data_u|0x0D);  //enable=1 and rs =1
    I2C_write (data_u|0x09);  //enable=0 and rs =1

    I2C_write (data_l|0x0D);  //enable =1 and rs =1
    I2C_write (data_l|0x09);  //enable=0 and rs =1

    I2C_stop();
}

void show(unsigned char *s)
{
    while(*s) 
    {
        dat(*s++);
    }
}
