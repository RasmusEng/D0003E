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
	GUI *gui;
	USARTSender *usart;
	LCD_Driver *lcd;
	int NorthQueueSize;
	int SouthQueueSize;
	int CarsOnBridge;
	int CarsPassedCurrent;
	bool NorthGreen;
	bool CarDirection;
	bool SouthGreen;
} Bridge;

#define initBridge(gui, usart, lcd) {initObject(), gui, usart, lcd, 0,0,0,0,false,false,true}

int handelInput(Bridge *self, int data);
int deQueue(Bridge *self, int side);

#endif /* BRIDGE_H_ */