/* 
 * File:   sarge_lab5_header_v001.h
 * Author: gus_sargent27
 *
 * Created on April 16, 2024, 9:19 PM
 */

#ifndef SARGE_LAB5_HEADER_V001_H
#define	SARGE_LAB5_HEADER_V001_H

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

#endif	/* SARGE_LAB5_HEADER_V001_H */

