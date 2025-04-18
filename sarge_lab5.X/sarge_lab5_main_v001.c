/*
 * File:   sarge_lab5_main_v001.c
 * Author: gus_sargent27
 *
 * Created on April 16, 2024, 9:18 PM
 */


#include "xc.h"
#include "sarge_lab5_header_v001.h"

#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void setup(void){
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9D;
    I2C2CONbits.I2CEN = 1;
    IFS3bits.MI2C2IF = 0;
    
    lcd_init();
}



int main(void) {
    setup();
   
    lcd_setCursor(0,0);
    
   //lcd_printChar('C');
    
    lcd_printStr("Hello, Gopher!");
    
    
    while(1){
     lcd_cmd(0b00011000);
        
     delay(150);
    }
    
    return 0;
}

