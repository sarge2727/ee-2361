/*
 * File:   sarge_lab6_lib_v002.c
 * Author: gus_sargent27
 *
 * Created on April 15, 2025, 8:10 PM
 */




#include "xc.h"
#include "sarge_lab6_header_v002.h"
#include "string.h"
#define SIZE 1024
#define SAMPLE 128

int buf[SIZE];
int end = SAMPLE;
int begin = 0;



void initBuffer(void) {
    for (int h = 0; h < SIZE; h++) {
        buf[h] = 0;
    }
}

void putVal(int val) {
    buf[end++] = val;
    end %= SIZE;
    begin++;
    begin %= SIZE;
}

int getAvg(void) {
    long int sum = 0;
    
    for (int i=0 ; i <SAMPLE; i++){
        sum += buf[(begin+i) % SIZE];
    }
       
    int avg = sum/SAMPLE;
    return  avg;
    
}

void delay(int ms){
    int l;
    for(l=1; l<=ms; l++){
        sarge_wait_1ms();
    }
}

void lcd_cmd(char command){
    I2C2CONbits.SEN = 1;     
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;   
    I2C2TRN = 0b01111100;   
    while(!IFS3bits.MI2C2IF); 
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b00000000;   
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = command;      
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN); 
}

void lcd_init(void){
    
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9D;
    I2C2CONbits.I2CEN = 1;
    IFS3bits.MI2C2IF = 0;
    
    delay(50);
    lcd_cmd(0b00111000);
    lcd_cmd(0b00111001); 
    lcd_cmd(0b00010100); 
    lcd_cmd(0b01110000); 
    lcd_cmd(0b01011110); 
    lcd_cmd(0b01101100); 
    
    delay(200);
    lcd_cmd(0b00111000); 
    lcd_cmd(0b00001100); 
    lcd_cmd(0b00000001); 
    
    delay(2);                      
    
}

void lcd_setCursor(char x, char y){
    lcd_cmd(0x80 | ((0x40 * x)+y));
}

void lcd_printChar(char myChar) {
    I2C2CONbits.SEN = 1; 
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100; 
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01000000; 
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = myChar; 
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1; 
    while(I2C2CONbits.PEN);   
}

void lcd_printStr(const char s[]){
char i;
    const char size = strlen(s);
    
    I2C2CONbits.SEN = 1;            // Initiate start condition
    while (I2C2CONbits.SEN == 1);   // Wait for SEN == 0; SEN will clear when
                                    // Start bit is complete
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = 0b01111100;           // 8-bits slave address and R/nW bit
    while (_MI2C2IF == 0);          // Wait
    
    for (i = 0; i < (size - 1); i++){  // Sending every char except last char
        _MI2C2IF = 0;                  // Clear flag
        I2C2TRN = 0b11000000;          // 8-bits control byte
                                       // CO = 0, RS = 1 for writing
        while (_MI2C2IF == 0);         // Wait
        _MI2C2IF = 0;                  // Clear flag
        I2C2TRN = s[i];                // 8-bits consisting of data
        while (_MI2C2IF == 0);         // Wait 
    }
        // Sending last byte of data
        _MI2C2IF = 0;                  // Clear flag
        I2C2TRN = 0b01000000;          // 8-bits control byte
                                       // CO = 0, RS = 1 for writing
        while (_MI2C2IF == 0);         // Wait
        _MI2C2IF = 0;                  // Clear flag
        I2C2TRN = s[size - 1];         // 8-bits consisting of data
        while (_MI2C2IF == 0);         // Wait
        _MI2C2IF = 0;                  // Clear flag
        I2C2CONbits.PEN = 1;           // Stop bit
        while (I2C2CONbits.PEN == 1);  // Wait for PEN == 0; PEN will clear when
                                       // Stop bit is complete
}

void ADC_init(void){
     // TRISAbits.TRISA0 = 1;
    AD1PCFG = 0xFFFE;       
    
    AD1CON1 = 0;            // reset everything before setup
    AD1CON1bits.ASAM  = 1;  // Sample Auto-Start Mode bit ON
    AD1CON1bits.SSRC = 0b010; // selecting Timer3 compare match
        
    
    AD1CON2 = 0;            // using at completion of each sequence
    
    AD1CON3 = 0;            //reset everything before setup
    AD1CON3bits.ADCS0 = 1;  // A/D Conversion Clock Period set at 2*Tcy
    AD1CON3bits.SAMC = 0x1; // sample time at 1 Tad
    
    AD1CSSL = 0;            // no scanning needed
    AD1CHS = 0;             // no input channels to be amplified

    
    // timer 3 
    T3CON = 0;
    T3CONbits.TCKPS = 0b10;     // prescaler  64
    PR3 = 1952;    // Set for 16 times per second = 16hz. (15625*64*62.5)^-1 = 16hz 
    //1952,15624
    TMR3 = 0;                  
    T3CONbits.TON = 1;
    
    IFS0bits.AD1IF = 0;     // clear A/D conversion interrupt
    IEC0bits.AD1IE = 1;     // enable A/D conversion interrupt
    AD1CON1bits.ADON = 1;   // turn on A/D
    
    // timer 2  
    T2CON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0b10; // prescaler 64.
    PR2 = 24999*2; // 24999 * 62.5 * 64 = 100ms
    
    
 
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 1;
   
}



