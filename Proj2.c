/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */
// PIC32MX370F512L Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
// USERID = No Setting
#pragma config FSRSSEL = PRIORITY_7     // Shadow Register Set Priority Select (SRS Priority 7)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2        // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (24x Multiplier)
#pragma config FPLLODIV = DIV_1       // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = XT            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_2           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (WDT Enabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is Disabled)
#pragma config JTAGEN = OFF              // JTAG Enable (JTAG Port Enabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)



#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING
#endif

#include <xc.h>
#include <plib.h>
#include <stdio.h>
#include "utils.h"
#include "swt.h"
#include "ssd.h"
#include <math.h>
/* TODO:  Include other files here if needed. */
int main(void){
//    TRISA = 0x0;
//    ANSELA = 0x0;
//    LATA = 0xFF;
    char hexString[80];
    char decString[80];
    LED_Init();
    LCD_Init();
    SSD_Init();
    SWT_Init();
    
    LCD_WriteStringAtPos("Team 1",0,0);
    while(1){
        sprintf(hexString, "Hex: %#04x", SWT_GetGroupValue());
        //sprintf(decString,"%04d", SWT_GetGroupValue());
        LCD_WriteStringAtPos(hexString, 1, 0);
        LED_SetGroupValue(SWT_GetGroupValue());
        update_SSD(SWT_GetGroupValue());
    }
}

void update_SSD(int value) {
    char dec[80];
    sprintf(dec, "%d", value);
    int hunds, tens, ones, tenths;
    char SSD1 = 0b0000000; //SSD setting for 1st SSD (LSD)
    char SSD2 = 0b0000000; //SSD setting for 2nd SSD
    char SSD3 = 0b0000000; //SSD setting for 3rd SSD 
    char SSD4 = 0b0000000; //SSD setting for 4th SSD (MSD)
    hunds = floor((int)dec / 1000);
    if (hunds > 0)
        SSD4 = hunds; //SSD4 = display_char[thous];
    else
        SSD4 = 17; //blank display
    tens = floor(((int)dec % 1000) / 100);
    if (hunds == 0 && tens == 0)
        SSD3 = 17; //blank display
    else
        SSD3 = tens;
    SSD2 = ones = floor((int)dec % 100 / 10);
    SSD1 = tenths = floor((int)dec % 10);
    SSD_WriteDigits(SSD1, SSD2, SSD3, SSD4, 0, 1, 0, 0);

}
