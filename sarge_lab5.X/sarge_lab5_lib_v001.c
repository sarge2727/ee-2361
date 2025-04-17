/*
 * File:   sarge_lab5_lib_v001.c
 * Author: gus_sargent27
 *
 * Created on April 16, 2024, 9:19 PM
 */


#include "xc.h"
#include "sarge_lab5_header_v001.h"
#include "string.h"

void delay(int ms){
    int i;
    for(i=1; i<=ms; i++){
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
    const char SIZE = strlen(s);
    
    I2C2CONbits.SEN = 1;            // Initiate start condition
    while (I2C2CONbits.SEN == 1);   // Wait for SEN == 0; SEN will clear when
                                    // Start bit is complete
    _MI2C2IF = 0;                   // Clear flag
    I2C2TRN = 0b01111100;           // 8-bits slave address and R/nW bit
    while (_MI2C2IF == 0);          // Wait
    
    for (i = 0; i < (SIZE - 1); i++){  // Sending every char except last char
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
        I2C2TRN = s[SIZE - 1];         // 8-bits consisting of data
        while (_MI2C2IF == 0);         // Wait
        _MI2C2IF = 0;                  // Clear flag
        I2C2CONbits.PEN = 1;           // Stop bit
        while (I2C2CONbits.PEN == 1);  // Wait for PEN == 0; PEN will clear when
                                       // Stop bit is complete
}

