#include "TinyTimber.h"
#include <stdbool.h>
#include "Bridge.h"

#define NorthEnQueue 0b0001
#define NorthDeQueue 0b0010
#define SouthEnQueue 0b0100
#define SouthDeQueue 0b1000

#define NORTH 1
#define SOUTH 0
#define PRINT(value, pos) ASYNC(self->lcd, printAt, PACK_PRINT(value, pos))
#define SENDSIGNAL ASYNC(self->usart, sendSignal, (self->NorthGreen << 0) | (!self->NorthGreen << 1)  | (self->SouthGreen << 2) | (!self->SouthGreen << 3))

int removeCarBridge(Bridge*, int);

int enQueue(Bridge *self, int side){
	if(side == NORTH){
		self->NorthQueueSize++;
		PRINT(self->NorthQueueSize, self->lcd->NorthScreenPos);
	}else if(side == SOUTH){
		self->SouthQueueSize++;
		PRINT(self->SouthQueueSize, self->lcd->SouthScreenPos);
	}
	return 0;
}

int setRedBoth(Bridge *self, __attribute__((unused)) int unUsed){
	self->NorthGreen = false;
	self->SouthGreen = false;
	
	return 0;
}

int convertBack(Bridge *self, int side){
	if(self->CarsSentCurrent >= 5){
		int oppositeQueue = self->CarDirection ? self->SouthQueueSize : self->NorthQueueSize;
		if(self->CarsOnBridge == 0 && oppositeQueue != 0){
			if(self->CarDirection == NORTH){
				self->NorthGreen = false;
				self->SouthGreen = true;
			}else{
				self->NorthGreen = true;
				self->SouthGreen = false;
			}
		}
		AFTER(MSEC(1000), self, convertBack, 0);
	}else{
		if(side == NORTH){
			self->NorthGreen = true;
			self->SouthGreen = false;
		}else if(side == SOUTH){
			self->NorthGreen = false;
			self->SouthGreen = true;
		}
	}
	SENDSIGNAL;
	
	return 0;
}

int deQueue(Bridge *self, int side){
	if(side == NORTH){
		self->NorthQueueSize--;
		setRedBoth(self, 0);
		AFTER(MSEC(1000), self, convertBack, side);
		PRINT(self->NorthQueueSize, self->lcd->NorthScreenPos);
	}else if(side == SOUTH){
		self->SouthQueueSize--;
		setRedBoth(self, 0);
		PRINT(self->SouthQueueSize, self->lcd->SouthScreenPos);
	}
	self->CarsSentCurrent++;
	self->CarsOnBridge++;
	PRINT(self->CarsOnBridge, self->lcd->CarsOnBridgePos);
	AFTER(MSEC(5000), self, removeCarBridge, 0);
	return 0;
}

int removeCarBridge(Bridge *self, __attribute__((unused)) int unUsed){
	self->CarsOnBridge--;
	PRINT(self->CarsOnBridge, self->lcd->CarsOnBridgePos);
	return 0;
}

int handelInput(Bridge *self, int data){
	switch(data){
		case NorthEnQueue:
			enQueue(self, NORTH);
			break;
		case NorthDeQueue:
			deQueue(self, NORTH);
			break;
		case SouthEnQueue:
			enQueue(self, SOUTH);
			break;
		case SouthDeQueue:
			deQueue(self, SOUTH);
			break;
		default: //Help a man has fallen into the river in LEGO City
			break;
	}
	return 0;
}