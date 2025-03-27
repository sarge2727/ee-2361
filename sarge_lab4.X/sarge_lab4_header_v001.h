/* 
 * File:   sarge_lab4_header_v001.h
 * Author: gus_sargent27
 *
 * Created on April 14, 2024, 3:54 PM
 */

#ifndef SARGE_LAB4_HEADER_V001_H
#define	SARGE_LAB4_HEADER_V001_H

#ifdef	__cplusplus
extern "C" {
#endif

    void sarge_wait_100us(void);
    void sarge_wait_1ms(void);
    void delay(int ms);
    void initServo(void);
    void setServo(int n);
    void initButton(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SARGE_LAB4_HEADER_V001_H */

