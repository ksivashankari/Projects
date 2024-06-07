
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

void SIM900A_init();
unsigned char rx();
void tx(unsigned char a);
void tx_string(const char *cmd);

void SIM900A_init()
{
    TXSTA = 0x20;
    RCSTA = 0x90;
    SPBRG = 31;
}

void tx(unsigned char a)
{
    TXREG = a;
    while (TXIF==0);
    TXIF=0;
}

unsigned char rx()
{
    while(RCIF==0);
    RCIF = 0;
    return RCREG;
}

void tx_string(const char *cmd)
{
    while (*cmd)
    {
        TXREG = *cmd++; 
        while (!TXIF); 
    }
}
