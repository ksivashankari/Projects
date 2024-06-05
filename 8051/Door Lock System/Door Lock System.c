#include<reg51.h>
#include <string.h> 
#define lcd_data P0

sbit IN1=P3^0;
sbit IN2=P3^1;
sbit IN3=P3^6;
sbit IN4=P3^7;

sbit rs=P2^0;
sbit rw=P2^1;
sbit en=P2^2;

sbit r1=P1^0;
sbit r2=P1^1;
sbit r3=P1^2;
sbit r4=P1^3;

sbit c1=P1^4;
sbit c2=P1^5;
sbit c3=P1^6;
sbit c4=P1^7;

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void delay(unsigned int ms);
unsigned char keypad();
unsigned char z;
void main()
{
	char password[5] = "5741";
	char Entered_Password[5];
	lcd_data=0x00;
	lcd_init();
	cmd(0x80);
	show("DIGITAL DOOR");
	cmd(0xc0);
	show("LOCK SYSTEM");
	delay(5000);
	cmd(0x01);
	cmd(0x80);
	show("TO UNLOCK DOOR");
	cmd(0xc0);
	show("Enter Password");
	delay(3500);
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
		delay(1000);
		if ((strcmp(password, Entered_Password)) == 0)
		{
			//Door Open
			cmd(0x01);
		  cmd(0x80);
		  show("DOOR OPENED");
		  IN1 = 1;
		  IN2 = 0;
    	IN3 = 1;
		  IN4 = 0;
			delay(1500);
			cmd(0x01);
			cmd(0x80);
			show("WELCOME HOME");
			IN1 = 0;
      IN2 = 0;
      IN3 = 0;
      IN4 = 0;
      delay(5000);		
			//Door Close
			cmd(0x01);
      cmd(0x80);
      show("DOOR CLOSED");
      IN1 = 0;
      IN2 = 1;
      IN3 = 0;
      IN4 = 1;
      delay(1500);  
      IN1 = 0;
      IN2 = 0;
      IN3 = 0;
      IN4 = 0;
		}
		else
		{
		  cmd(0x80);
		  show("WRONG PASSWORD");
			cmd(0xc0);
			show("TRY AGAIN");
			delay(3500);
			cmd(0x01);
	   	IN1 = 0;
	  	IN2 = 0;
		  IN3 = 0;
		  IN4 = 0;
			cmd(0x80);
	    show("PASSWORD-");
		}
	}
}

unsigned char keypad()
{
    while(1)
    {
        c1=c2=c3=c4=1;
        r2=r3=r4=1;
        r1=0;
        if(c1==0)
        {
          while(c1==0);
					dat('/');
					return '/';
        }
        else if(c2==0)
        {
          while(c2==0);
				  dat('9');
					return '9';
        }
        else if(c3==0)
        {
          while(c3==0);
					dat('8');
					return '8';
        }
				else if(c4==0)
        {
          while(c4==0);
					dat('7');
					return '7';
        }
        r1=r3=r4=1;
        r2=0;
        if(c1==0)
        {
          while(c1==0);
					dat('*');
					return '*';
        }
        else if(c2==0)
        {
          while(c2==0);
					dat('6');
					return '6';
        }
        else if(c3==0)
        {
          while(c3==0);
					dat('5');
					return '5';
        }
				else if(c4==0)
        {
          while(c4==0);
					dat('4');
					return '4';
        }
        r1=r2=r4=1;
        r3=0;
        if(c1==0)
        {
          while(c1==0);
					dat('-');
					return '-';
        }
        else if(c2==0)
        {
          while(c2==0);
					dat('3'); 
					return '3';
        }
        else if(c3==0)
        {
          while(c3==0);
					dat('2');
					return '2';
        }
				else if(c4==0)
        {
          while(c4==0);
					dat('1');
					return '1';
        }
        r1=r3=1;
        r4=0;
        if(c1==0)
        {
					while(c1==0);
					dat('+');
					return '+';
        }
				else if (c2 == 0) 
				{
          while (c2 == 0);
          dat('@');
          return '@';
        }
        else if(c3==0)
        {
          while(c3==0);
					dat('0');
					return '0';
        }
				else if (c4 == 0)
				{
          while (c4 == 0);
          dat('#');
          return '#';
        }
    }
}

void lcd_init()
{
    cmd(0x38);
    cmd(0x0e);
    cmd(0x01);
    cmd(0x06);
    cmd(0x0c);
    cmd(0x80);
}

void cmd(unsigned char a)
{
    lcd_data=a;
    rs=0;
    rw=0;
    en=1;
    delay(1);
    en=0;
}

void dat(unsigned char b)
{
    lcd_data=b;
    rs=1;
    rw=0;
    en=1;
    delay(1);
    en=0;
}

void show(unsigned char *s)
{
    while(*s) 
    {
        dat(*s++);
    }
}

void delay(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<100;j++);
}
