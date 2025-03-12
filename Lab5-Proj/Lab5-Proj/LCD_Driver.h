#ifndef LCD_Driver_H_
#define LCD_Driver_H_ 

#include "TinyTimber.h"
#include "LCD_Driver.h"
#include <stdbool.h>
#include <avr/io.h>
#include <stdint.h>

typedef struct
{
	Object super;
	int ConstNorthScreenPos;
	int ConstSouthScreenPos;
	int ConstCarsOnBridgePos;
} LCD_Driver;

#define initLCD_Driver() {initObject(),4,0,2}
	
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

int startSequence(LCD_Driver *self, int first);

#endif