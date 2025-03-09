#include "TinyTimber.h"
#include <stdbool.h>
#include "Bridge.h"

#define NorthEnQueue 0b0001
#define NorthDeQueue 0b0010
#define SouthEnQueue 0b0100
#define SouthDeQueue 0b1000
#define NORTH 1
#define SOUTH 0
#define PRINT(value, pos) ASYNC(self->gui, printAt, PACK_PRINT(value, pos))
#define SENDSIGNAL ASYNC(self->usart, sendSignal, (self->NorthGreen << 0) | (!self->NorthGreen << 1)  | (self->SouthGreen << 2) | (!self->SouthGreen << 3))

int increaseCarsOnBridge(Bridge*, int);
int switchSide(Bridge*, int);

int deQueue(Bridge *self, int side){
	if(self->CarsPassedCurrent<10){
		if(self->NorthGreen && (self->CarDirection == NORTH)){
			if(self->NorthQueueSize > 0){
				self->NorthQueueSize--;
				PRINT(self->NorthQueueSize, self->gui->NorthScreenPos);
				increaseCarsOnBridge(self, 0);
			}else{
				switchSide(self, 0);
			}
		}else if(self->SouthGreen && (self->CarDirection == SOUTH)){
			if(self->SouthQueueSize > 0){
				self->SouthQueueSize--;
				PRINT(self->SouthQueueSize, self->gui->SouthScreenPos);
				increaseCarsOnBridge(self, 0);
			}else{
				switchSide(self, 0);
			}
		}
	}else{
		int opposite = self->CarDirection ? self->SouthQueueSize : self->NorthQueueSize;
		
		if(opposite){
			switchSide(self, 0);
		}
	}
	AFTER(SEC(1), self, deQueue, 0);
	return 0;
}

int removeCarBridge(Bridge *self, __attribute__((unused)) int unUsed){
	if(self->CarsOnBridge > 0){ //Should not be needed but added for saftey
		self->CarsOnBridge--;
		self->CarsPassedCurrent++;
		PRINT(self->CarsOnBridge, self->gui->CarsOnBridgePos);
	}
	return 0;
}

int increaseCarsOnBridge(Bridge *self, int __attribute__((unused)) unUsed){
	self->CarsOnBridge++;
	PRINT(self->CarsOnBridge, 2);
	AFTER(SEC(5), self, removeCarBridge, 0);
	return 0;
}

int enQueue(Bridge *self, int side){
	if(side == NORTH){
		self->NorthQueueSize++;
		PRINT(self->NorthQueueSize, self->gui->NorthScreenPos);
	}else if(side == SOUTH){
		self->SouthQueueSize++;
		PRINT(self->SouthQueueSize, self->gui->SouthScreenPos);
	}
	return 0;
}

int setRedBoth(Bridge *self, int __attribute__((unused)) unUsed){
	self->NorthGreen = false;
	self->SouthGreen = false;
	SENDSIGNAL;
	return 0;
}

int switchSide(Bridge *self, int __attribute__((unused)) unUsed){
	self->CarsPassedCurrent = 0;
	if(self->CarsOnBridge != 0){
		if(self->NorthGreen || self->SouthGreen) setRedBoth(self, 0);
		AFTER(MSEC(1250),self, switchSide, 0);
	}else{
		if(self->CarDirection){
			self->SouthGreen = true;
			self->NorthGreen = false;
			self->CarDirection = SOUTH;
		}else if(!self->CarDirection){
			self->NorthGreen = true;
			self->SouthGreen = false;
			self->CarDirection = NORTH;
		}
		SENDSIGNAL;
	}
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