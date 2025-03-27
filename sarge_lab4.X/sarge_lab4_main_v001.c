/*
 * File:   sarge_lab4_main_v001.c
 * Author: gus_sargent27
 *
 * Created on April 14, 2024, 3:54 PM
 */


#include "xc.h"
#include "sarge_lab4_header_v001.h"

#pragma config ICS = PGx1           // Comm Channel Select (Emulator EMUC1/EMUD1 
                                    // pins are shared with PGC1/PGD1).
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (Watchdog Timer is 
                                    // disabled).
#pragma config GWRP = OFF           // General Code Segment Write Protect 
                                    // (Writes to program memory are allowed).
#pragma config GCP = OFF            // General Code Segment Code Protect (Code 
                                    // protection is disabled).
#pragma config JTAGEN = OFF         // JTAG Port Enable (JTAG port is disabled).

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI        // I2C1 Pin Location Select (Use default 
                                    // SCL1/SDA1 pins).
#pragma config IOL1WAY = OFF        // IOLOCK Protection (IOLOCK may be changed 
                                    // via unlocking seq).
#pragma config OSCIOFNC = ON        // Primary Oscillator I/O Function 
                                    // (CLKO/RC15 functions as I/O pin).
#pragma config FCKSM = CSECME       // Clock Switching and Monitor (Clock 
                                    // switching is enabled, Fail-Safe Clock 
                                    // Monitor is enabled).
#pragma config FNOSC = FRCPLL       // Oscillator Select (Fast RC Oscillator // with PLL module (FRCPLL)).

#define BUFFSIZE 3


volatile unsigned long  int overflow = 0;
volatile unsigned long  int lastEventTime = 0; // calculate the time of the last event
volatile unsigned int prevState = 0; //to track if 0- relase or 1- if press

//Buffer variables
volatile unsigned long int buffer[BUFFSIZE] = {0, 0, 0};  //Buffer with size 3 to place the times in 
volatile unsigned long int writeIdx = 0;
volatile unsigned long int diff = 0;


void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void) {
    _T2IF = 0;
    overflow++;
    

}

void writeBuffer(unsigned long int x){
    
        buffer[writeIdx++] = x;
        writeIdx %= BUFFSIZE;

    
}



void __attribute__((__interrupt__, __auto_psv__)) _IC1Interrupt(void) {
   _IC1IF = 0; // don?t forget to reset your flags to zero!

   
   unsigned long int currentEventTime = (IC1BUF+((PR2+1)*overflow));
   diff = currentEventTime - lastEventTime;
   
   
    //Compare current and last event times. if value is large enough than we move to the next part, if not then it is a bounce
    if ( diff > 125 ) {// 
         lastEventTime = currentEventTime ;
         

        if (prevState == 0) { //checking press or release
            prevState = 1 ;  //change the state to a press
            writeBuffer(lastEventTime);
            


           
                
           }
            
        else { //meaning there was a button press, then change state to a release 
            prevState = 0;
             
        }
        
    } 
    
   
  
}

    

 
void setup(void){
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    initServo();
    initButton();
    
}


int main(void) {
    setup();
    unsigned long int tclick = 0;
    unsigned long int current = 0;
    unsigned long int tnew = 0;
    unsigned long int told = 0;
    
    while(1) {
        current = (overflow*62500)+TMR2;
        told = buffer[writeIdx];
        tnew = buffer[(writeIdx+2)%3];

        
        if((tnew-told)<62500/2){
            tclick = tnew; 
            
        
        }
        
        if((current-tclick)>62500*2){
            setServo(5000);
        }
        else{
            setServo(1000);
        }
        
        
    
    
    
        
    

    }                   
}
                
                            
        
    
        


  
        
    

    
             


            
        
    
    
    

