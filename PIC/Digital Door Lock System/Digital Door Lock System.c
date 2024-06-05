
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
#include <string.h> 
#include "LCD.h"
#define _XTAL_FREQ 20000000

#define c1 RD0 
#define c2 RD1
#define c3 RD2 

#define r1 RD4 
#define r2 RD5 
#define r3 RD6 
#define r4 RD7 

#define motor RC3

unsigned char keypad();
unsigned char z;

void main()
{
    char password[5] = "123*";
	  char Entered_Password[5];
    TRISB=0x00;
    TRISC=0x00;
    TRISD=0x0f;
    lcd=0x00;
    lcd_init();
    cmd(0x80);
   	show("DIGITAL DOOR");
	  cmd(0xc0);
	  show("LOCK SYSTEM");
  	__delay_ms(5000);
  	cmd(0x01);
	  cmd(0x80);
	  show("TO UNLOCK DOOR");
	  cmd(0xc0);
	  show("Enter Password");
	  __delay_ms(3500);
	  cmd(0x01);
	  cmd(0x80);
  	show("PASSWORD-");
    while(1)
    {
        for(z=0;z<4;z++)
		    {
          Entered_Password[z] = keypad();
		    }
	     	Entered_Password[4] = '\0';
	     	__delay_ms(1000);
	    	if ((strcmp(password, Entered_Password)) == 0)
	    	{
            //Door Open
			      cmd(0x01);
		        cmd(0x80);
		        show("DOOR OPENED");
		        motor=1;
            __delay_ms(2);
            motor=0;
            __delay_ms(1500);
			      cmd(0x01);
			      cmd(0x80);
			      show("WELCOME HOME");
		
			      //Door Close
			      cmd(0x01);
            cmd(0x80);
            show("DOOR CLOSED");
            motor=1;
            __delay_ms(1);
            motor=0;
            __delay_ms(1500);
	    	}
	     	else
	    	{
            cmd(0x80);
		        show("WRONG PASSWORD");
			      cmd(0xc0);
			      show("TRY AGAIN");
			      __delay_ms(3500);
			      cmd(0x01);
			      cmd(0x80);
	          show("PASSWORD-");
		    }
    }
}

unsigned char keypad()
{
    while(1)
    {
        c1=c2=c3=0;
        r2=r3=r4=0;
        r1=1;
        if(c1==1)
        {
            while(c1==1);
            dat('1');
            return '1';
        }
        else if(c2==1)
        {
            while(c2==1);
            dat('2');
            return '2';
        }
        else if(c3==1)
        {
            while(c3==1);
            dat('3');
            return '3';
        }
        r1=r3=r4=0;
        r2=1;
        if(c1==1)
        {
            while(c1==1);
            dat('4');
            return '4';
        }
        else if(c2==1)
        {
            while(c2==1);
            dat('5');
            return '5';
        }
        else if(c3==1)
        {
            while(c3==1);
            dat('6');
            return '6';
        }
        r1=r2=r4=0;
        r3=1;
        if(c1==1)
        {
            while(c1==1);
            dat('7');
            return '7';
        }
        else if(c2==1)
        {
            while(c2==1);
            dat('8'); 
            return '8';
        }
        else if(c3==1)
        {
            while(c3==1);
            dat('9'); 
            return '9';
        }
        r1=r2=r3=0;
        r4=1;
        if(c1==1)
        {
            while(c1==1);
            dat('*'); 
            return '*';
        }
        else if(c2==1)
        {
            while(c2==1);
            dat('0');  
            return '0';
        }
        else if(c3==1)
        {
            while(c3==1);
            dat('#'); 
            return '#';
        }
    }
}
