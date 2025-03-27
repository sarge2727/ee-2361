/*
 * File:   sarge_lab4_impl_v001.c
 * Author: gus_sargent27
 *
 * Created on April 14, 2024, 3:55 PM
 */


#include "xc.h"
#include "sarge_lab4_header_v001.h"

#define PERIOD 2

void delay(int ms){
    int i;
    for(i=1; i<=ms; i++){
        sarge_wait_1ms();
    }
}

void initServo(void){
    TRISBbits.TRISB6 = 0;
    
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPOR3bits.RP6R = 18;
    RPINR7bits.IC1R = 8;
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    T3CONbits.TON = 0;
    T3CONbits.TCKPS = 0b01;  // PRE 8
    T3CONbits.TGATE = 0;
    T3CONbits.TCS = 0;
    TMR3 = 0;
    PR3 = 39999;
    
    OC1CON = 0;
    OC1R = 1000;
    OC1RS = 1000;
    OC1CONbits.OCTSEL = 1;
    OC1CONbits.OCM = 0b110;
    
    T3CONbits.TON = 1;   
}

void setServo(int n){
    OC1RS = n;
}

void initButton(void){
    //  IC1 setup
    IC1CON = 0;
    IC1CONbits.ICTMR = 1;
    IC1CONbits.ICM = 0b001; // every edge 
    _IC1IF = 0;
    _IC1IE = 1;
    
    
    
    // TMR2 Set Up
    TRISBbits.TRISB8 = 1;
    CNPU2bits.CN22PUE = 1;
    
    T2CONbits.TON = 0;
    T2CONbits.TCKPS = 0b11;         // PRE = 256
    T2CONbits.TGATE = 0;
    T2CONbits.TSIDL = 0;
    T2CONbits.TCS = 0;
    
    TMR2 = 0;
    PR2 = 62499; // 1 sec period. 256*62500*62.5 = 1s
    CNPU2bits.CN22PUE = 1;
    _T2IF = 0;
    _T2IE = 1;
    T2CONbits.TON = 1;
    
}

