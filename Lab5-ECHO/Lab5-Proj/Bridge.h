#include "TinyTimber.h"

#ifndef BRIDGE_H_
#define BRIDGE_H_

typedef struct
{
	Object super;
	int southQueue;
	int northQueue;
	int carsPassed;
	int carsOn;
} Bridge;

#define initBridge(south, north, passed, on) {initObject(), south, north, passed, on};



#endif