/*
 * LCC_Driver.h
 *
 * Created: 2025-01-23 10:11:39
 *  Author: Joel & Rasmus
 */ 
#ifndef LCD_Driver_H_
#define LCD_Driver_H_ 
#include <stdint.h>

void LCD_Init(void);

void LCD_update(unsigned char data1, unsigned char data2);

void writeChar(char ch, int pos);

void writeLong(long i);

void printAt(uint16_t num, int pos);

void switchIndicator();
#endif