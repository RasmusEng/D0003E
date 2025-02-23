/*
 * LCC_Driver.h
 *
 * Created: 2025-01-23 10:11:39
 *  Author: Joel & Rasmus
 */ 
#ifndef LCD_Driver_H_
#define LCD_Driver_H_ 
#include <stdint.h>
//TODO finx so that printAt ans switchIndicator can be called with SYNC and ASYNC
void LCD_Init(void);

void printAt(int num, int pos);

void switchIndicator();
#endif