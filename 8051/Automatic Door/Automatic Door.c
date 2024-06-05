#include<reg51.h>
#define lcd_data P3
sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;
sbit Servo1 = P2^0;
sbit Servo2 = P2^1;
sbit IR_sensor = P0^0;
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void delay(unsigned int ms);
void timer_delay(unsigned int x,y);
void main()
{
	lcd_data=0x00;
  lcd_init();
	IR_sensor = 0xFF;
	Servo1 = 0x00;
	Servo2 = 0x00;
	while(1)
	{
		if(IR_sensor == 0)
		{	
			cmd(0x80);
      show("Door Opened");
			Servo1 = 1;
		  timer_delay(0xFC,0xB5);
		  Servo1 = 0;
		  Servo2 = 1;
		  timer_delay(0xF8,0xCD);
		  Servo2 = 0;
		  delay(1000);
		}
		else
		{
			cmd(0x80);
      show("Door closed");
			Servo1 = 1;
		  timer_delay(0xF8,0xCD);
		  Servo1 = 0;
			Servo2 = 1;
		  timer_delay(0xFC,0xB5);
		  Servo2 = 0;
		  delay(1000);
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

void timer_delay(unsigned int x,y)
{
	TMOD=0x01;
	TH0=x;
	TL0=y;
	TR0=1;
	while(TF0==0);
	TF0=0;
	TR0=0;
}
