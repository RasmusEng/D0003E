#ifndef BRIDGE_H_
#define BRIDGE_H_

#include "USARTSender.h"
#include "TinyTimber.h"
#include "LCD_Driver.h"
#include <stdbool.h>
#include "GUI.h"

typedef struct  
{
	Object super;
	USARTSender *usart;
	LCD_Driver *lcd;
	int NorthQueueSize;
	int SouthQueueSize;
	int CarsOnBridge;
	int CarsSentCurrent;
	bool forceRED;
	bool NorthGreen;
	bool CarDirection;
	bool SouthGreen;
} Bridge;

#define initBridge(usart, lcd) {initObject(), usart, lcd, 0,0,0,0,false, false,false,false}

int handleInput(Bridge *self, int data);
int deQueue(Bridge *self, int side);

#endif /* BRIDGE_H_ */