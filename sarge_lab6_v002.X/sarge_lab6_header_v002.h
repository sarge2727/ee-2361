/* 
 * File:   sarge_lab6_header_v002.h
 * Author: gus_sargent27
 *
 * Created on April 15, 2025, 8:09 PM
 */

#ifndef SARGE_LAB6_HEADER_V002_H
#define	SARGE_LAB6_HEADER_V002_H

#ifdef	__cplusplus
extern "C" {
#endif

    void lcd_cmd(char command);
    void lcd_init(void);
    void lcd_setCursor(char x, char y);
    void lcd_printChar(char myChar);
    void lcd_printStr(const char *s);
    void delay(int milliseconds);
    void sarge_wait_1ms(void);
    


#ifdef	__cplusplus
}
#endif

#endif	/* SARGE_LAB6_HEADER_V002_H */

