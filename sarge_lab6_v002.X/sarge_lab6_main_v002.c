/*
 * File:   sarge_lab6_main_v002.c
 * Author: gus_sargent27
 *
 * Created on April 15, 2025, 8:11 PM
 */


#include "xc.h"
#include <stdio.h>
#include "sarge_lab6_header_v002.h"
#include "string.h"


#pragma config ICS = PGx1 // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,
                                // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void __attribute__((__interrupt__, __auto_psv__)) _ADC1Interrupt(void) {
    IFS0bits.AD1IF = 0;
    putVal(ADC1BUF0);
    
}

void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void) {
    _T2IF = 0;
    int avgVal;
    avgVal = getAvg();
    char to_prinr[20];
    sprintf(to_prinr, "%6.4f V", (3.3 / 1024) * avgVal);
    lcd_setCursor(0, 0);
    lcd_printStr(to_prinr);
}

void setup(void){
    CLKDIVbits.RCDIV = 0; 
    AD1PCFG = 0x9fff;
    lcd_init();
    initBuffer();
    ADC_init();
}


int main(void) {
    setup();
    
     // lcd_printStr("Hello");
    while (1){

        
    }
    
    return;
}