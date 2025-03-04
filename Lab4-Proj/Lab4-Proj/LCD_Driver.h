/*
 * LCC_Driver.h
 *
 * Created: 2025-01-23 10:11:39
 *  Author: Joel & Rasmus
 */ 

#ifndef LCD_Driver_H_
#define LCD_Driver_H_ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "TinyTimber.h"
#include "LCD_Driver.h"

typedef struct
{
	Object super;
} LCD_Driver;

#define initLCD_Driver() {initObject()};
	
struct Packed {
	unsigned int num  : 7;
	unsigned int pos  : 3;
};

union PrintPun {
	struct Packed args;
	int map;
};

#define PACK_PRINT(num, pos) ((union PrintPun){ .args = { num, pos } }).map

int printAt(LCD_Driver *self, int);

int switchIndicator(LCD_Driver *self, int);
#endif