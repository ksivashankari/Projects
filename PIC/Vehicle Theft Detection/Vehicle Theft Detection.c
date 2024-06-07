
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
#include "GSM.h"
#include "DC_Motor.h"

#define theft_mode RB3
#define USER_NUM "123456789" //USER NUMBER

int Engine_Lock = 0;

void GSM_init();
void SMS();
void Engine_Stopped_SMS();

void main()
{
    TRISB0 = 0x00;
    TRISB1 = 0x00;
    TRISB2 = 0x00;
    TRISB3 = 0xFF;
    TRISD = 0x00;
    TRISC6 = 0; // Tx
    TRISC7 = 1; // Rx
    TRISC0 = 0;
    TRISC1 = 0;
    SIM900A_init();
    lcd_data = 0x00;
    lcd_init();
    cmd(0x80);
    show("VEHICLE THEFT");
    cmd(0xc0);
    show("DETECTION");
    __delay_ms(5000);
    GSM_init();
    while(1)
    {
        if(theft_mode == 1 && !Engine_Lock)
        {
            cmd(0x80);
            show("VEHICLE RUNNING");
            cmd(0xc0);
            show("IN THEFT MODE");
            __delay_ms(3000);
            cmd(0x01);
            SMS();
            Engine_Lock = 1;
        }
        else if (Engine_Lock)
        {
            char rx_cmd = rx();
            tx(rx_cmd);
            if(rx_cmd == 'S')
            {
                Engine_stops();
                Engine_Stopped_SMS();
            }
        }
        else 
        {
            cmd(0x80);
            show("VEHICLE RUNNING");
            cmd(0xc0);
            show("IN USER MODE");
            Engine_runs();
        }
    }
}

void GSM_init()
{
    tx_string("AT\r\n");
    __delay_ms(500);
    tx_string("ATE0\r\n");
    __delay_ms(500);
}

void SMS()
{
    // Send SMS through GSM module
    cmd(0x80);
    show("SENDING SMS...");
    __delay_ms(3500);
    tx_string("AT+CMGF=1\r\n"); // Set SMS to text mode
    __delay_ms(2000);
    tx_string("AT+CMGS=\"" USER_NUM "\"\r\n"); // Set recipient phone number
    __delay_ms(2000);
    cmd(0x80);
    show("SMS RECEIVED");
    tx_string("Vehicle is in theft mode!\r\n"); // Set SMS text
    __delay_ms(2000);
    tx(26); // ASCII code of CTRL+Z to send the SMS
    __delay_ms(1000);
}

void Engine_Stopped_SMS()
{
    tx_string("\r\nAT+CMGF=1\r\n"); // Set SMS to text mode
    __delay_ms(2000);
    tx_string("AT+CMGS=\"" USER_NUM "\"\r\n"); // Set recipient phone number
    __delay_ms(2000);
    cmd(0xc0);
    tx_string("Engine Stopped\r\n"); // Set SMS text
    __delay_ms(2000);
    tx(26); // ASCII code of CTRL+Z to send the SMS
    __delay_ms(1000);
}
