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
#include <stdio.h>
#include <string.h>
#include "I2C-LCD.h"

#define r1 RD0
#define r2 RD1
#define r3 RD2
#define r4 RD3

#define c1 RD4
#define c2 RD5
#define c3 RD6
#define c4 RD7

void calculation();

long long a = 0;
long long b = 0;
long long c = 0;
char operator = '\0';
char c_value[50];

void main()
{
    TRISD = 0xf0;
    I2C_init();
    lcd_init();
    while(1)
    {
        c1 = c2 = c3 = c4 = 0;
        r2 = r3 = r4 = 0;
        r1 = 1;
        if(c1 == 1)
        {
            __delay_ms(50);
            while(c1 == 1);
            dat('7');
            if (operator == '\0')
            {
                a = a * 10 + 7;
            }
            else
            {
                b = b * 10 + 7;
            }
        }
        else if(c2 == 1)
        {
            __delay_ms(50);
            while(c2 == 1);
            dat('8');
            if (operator == '\0')
            {
                a = a * 10 + 8;
            }
            else
            {
                b = b * 10 + 8;
            }
        }
        else if(c3 == 1)
        {
            __delay_ms(50);
            while(c3 == 1);
            dat('9');
            if (operator == '\0')
            {
                a = a * 10 + 9;
            }
            else
            {
                b = b * 10 + 9;
            }
         }
        else if(c4 == 1)
        {
            __delay_ms(50);
            while(c4 == 1);
            dat('/');
            operator = '/'; 
        }
        
        r1 = r3 = r4 = 0;
        r2 = 1;
        if(c1 == 1)
        {
            __delay_ms(50);
            while(c1 == 1);
            dat('4');
            if (operator == '\0')
            {
                a = a * 10 + 4;
            }
            else
            {
                b = b * 10 + 4;
            }
        }
        else if(c2 == 1)
        {
            __delay_ms(50);
            while(c2 == 1);
            dat('5');  
            if (operator == '\0')
            {
                a = a * 10 + 5;
            }
            else
            {
                b = b * 10 + 5;
            }
        }
        else if(c3 == 1)
        {
            __delay_ms(50);
            while(c3 == 1);
            dat('6');
            if (operator == '\0')
            {
                a = a * 10 + 6;
            }
            else
            {
                b = b * 10 + 6;
            }
        }
        else if(c4 == 1)
        {
            __delay_ms(50);
            while(c4 == 1);
            dat('*');
            operator = '*'; 
        }
        
        r1 = r2 = r4 = 0;
        r3 = 1;
        if(c1 == 1)
        {
            __delay_ms(50);
            while(c1 == 1);
            dat('1');
            if (operator == '\0')
            {
                a = a * 10 + 1;
            }
            else
            {
                b = b * 10 + 1;
            }
        }
        else if(c2 == 1)
        {
            __delay_ms(50);
            while(c2 == 1);
            dat('2');
            if (operator == '\0')
            {
                a = a * 10 + 2;
            }
            else
            {
                b = b * 10 + 2;
            }
        }
        else if(c3 == 1)
        {
            __delay_ms(50);
            while(c3 == 1);
            dat('3');
            if (operator == '\0')
            {
                a = a * 10 + 3;
            }
            else
            {
                b = b * 10 + 3;
            }
        }
        else if(c4 == 1)
        {
            __delay_ms(50);
            while(c4 == 1);
            dat('-');
            operator = '-'; 
        }
        
        r1 = r2 = r3 = 0;
        r4 = 1;
        if(c1 == 1)
        {
            __delay_ms(50);
            while(c1 == 1);
            cmd(0x01);
        }
        else if(c2 == 1)
        {
            __delay_ms(50);
            while(c2 == 1);
            dat('0');
            if (operator == '\0')
            {
                a = a * 10 + 0;
            }
            else
            {
                b = b * 10 + 0;
            }
        }
        else if(c3 == 1)
        {
            __delay_ms(50);
            while(c3 == 1);
            show(" = ");
            cmd(0xc0);
            calculation();
        }
        else if(c4 == 1)
        {
            __delay_ms(50);
            while(c4 == 1);
            dat('+');
            operator = '+'; 
        }
    }
}

void calculation()
{
    switch(operator)
    {
    case '+':
        c = a + b;
        sprintf(c_value,"%lld",c);
        show(c_value);
        break;
    case '-':
        c = a - b;
        sprintf(c_value,"%lld",c);
        show(c_value);
        break;
    case '*':
        c = a * b;
        sprintf(c_value,"%lld",c);
        show(c_value);
        break;
    case '/':
        if(b != 0)
        {
            c = a / b;
            sprintf(c_value,"%lld",c);
            show(c_value);
        }
        else
        {
            show("Error");
            cmd(0xc0);
            show("Can't Div By 0");
        }
        break;
    default:
        break;
    }
    //reset
    a = 0;
    b = 0;
    c = 0;
    operator = '\0';
}
