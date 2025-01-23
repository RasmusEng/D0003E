/*
 * LCC-Driver.h
 *
 * Created: 2025-01-23 10:11:39
 *  Author: joel
 */ 


#ifndef LCC-Driver_H_
#define LCC-Driver_H_

void LCD_Init(void);

void LCD_update(unsigned char data1, unsigned char data2);

void writeChar(int ch, int pos);

#endif /* LCC-Driver_ */