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
#define MAX_CARS_BEFORE_SWITCH 5
int normalSWITCH(Bridge *self, int side);
int convertBack(Bridge *self, int side);
int removeCarBridge(Bridge*, int);

int enQueue(Bridge *self, int side){
	if(side == NORTH){
		self->NorthQueueSize++;
		PRINT(self->NorthQueueSize, self->lcd->ConstNorthScreenPos);
	}else if(side == SOUTH){
		self->SouthQueueSize++;
		PRINT(self->SouthQueueSize, self->lcd->ConstSouthScreenPos);
	}
	if(self->CarsOnBridge == 0 && self->NorthQueueSize == 1 && self->SouthQueueSize == 0){
		ASYNC(self, normalSWITCH, 0);
	}else if(self->CarsOnBridge == 0 && self->SouthQueueSize == 1 && self->NorthQueueSize == 0){
		ASYNC(self, normalSWITCH, 0);
	}else if(!self->NorthGreen && !self->SouthGreen && !self->forceRED){
		ASYNC(self, normalSWITCH, 0);
	}
	return 0;
}

int normalSWITCH(Bridge *self, int side){
	if(self->forceRED){
		return 0;
	}
	if(side == NORTH){
		if(self->NorthQueueSize){
			if(self->CarDirection == NORTH){
				self->NorthGreen = true;
				self->SouthGreen = false;
				self->CarDirection = NORTH;
				SENDSIGNAL;
			}else{
				AFTER(MSEC(1250), self, normalSWITCH, NORTH);
			}
			
		}else if(self->SouthQueueSize){
			if(self->CarsOnBridge){
				AFTER(MSEC(1250), self, normalSWITCH, NORTH);
			}else{
				self->SouthGreen = true;
				self->NorthGreen = false;
				self->CarDirection = SOUTH;
				self->CarsSentCurrent = 0;
				SENDSIGNAL;
			}
		}else{
			self->NorthGreen = false;
			self->SouthGreen = false;
			SENDSIGNAL;
		}
	}else if (side == SOUTH){
		if(self->SouthQueueSize){
			if(self->CarDirection == SOUTH){
				self->SouthGreen = true;
				self->NorthGreen = false;
				self->CarDirection = SOUTH;
				SENDSIGNAL;
			}else{
				AFTER(MSEC(1250), self, normalSWITCH, SOUTH);
			}
		}else if(self->NorthQueueSize){
			if(self->CarsOnBridge){
				AFTER(MSEC(1250), self, normalSWITCH, SOUTH);
			}else{
				self->NorthGreen = true;
				self->SouthGreen = false;
				self->CarDirection = NORTH;
				self->CarsSentCurrent = 0;
				SENDSIGNAL;
			}
		}else{
			self->NorthGreen = false;
			self->SouthGreen = false;
			SENDSIGNAL;
		}
	}
	return 0;
}

int convertBack(Bridge *self, int side){
	int oppositeQueu;
	if(side == NORTH){
		oppositeQueu = self->SouthQueueSize;
	}else{
		oppositeQueu = self->NorthQueueSize;
	}
	if(self->CarsSentCurrent > MAX_CARS_BEFORE_SWITCH && oppositeQueu){
		if(self->CarsOnBridge != 0){
			self->forceRED = true;
			AFTER(MSEC(1250), self, convertBack, side);
		}else{
			self->forceRED = false;
			self->CarsSentCurrent = 0;
			bool sideNew = !side;
			self->CarDirection = !self->CarDirection;
			ASYNC(self, normalSWITCH, sideNew);
		}
	}else{
		ASYNC(self, normalSWITCH, side);
	}
	
	return 0;
}

int deQueue(Bridge *self, int side){
	if(side == NORTH){
		self->NorthQueueSize--;
		self->CarsSentCurrent++;
		self->CarsOnBridge++;
		AFTER(MSEC(1000), self, convertBack, side);
		PRINT(self->NorthQueueSize, self->lcd->ConstNorthScreenPos);
	}else if(side == SOUTH){
		self->SouthQueueSize--;
		self->CarsSentCurrent++;
		self->CarsOnBridge++;
		AFTER(MSEC(1000), self, convertBack, side);
		PRINT(self->SouthQueueSize, self->lcd->ConstSouthScreenPos);
	}
	PRINT(self->CarsOnBridge, self->lcd->ConstCarsOnBridgePos);
	AFTER(MSEC(5000), self, removeCarBridge, 0);
	return 0;
}

int removeCarBridge(Bridge *self, __attribute__((unused)) int unUsed){
	self->CarsOnBridge--;
	PRINT(self->CarsOnBridge, self->lcd->ConstCarsOnBridgePos);
	return 0;
}

int handleInput(Bridge *self, int data){
	switch(data){
		case NorthEnQueue:
			ASYNC(self, enQueue, NORTH);
			break;
		case NorthDeQueue:
			ASYNC(self, deQueue, NORTH);
			break;
		case SouthEnQueue:
			ASYNC(self, enQueue, SOUTH);
			break;
		case SouthDeQueue:
			ASYNC(self, deQueue, SOUTH);
			break;
		default: //Help a man has fallen into the river in LEGO City
			break;
	}
	return 0;
}