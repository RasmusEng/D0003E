#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include "TinyTimber.h"
#include <stdbool.h>
#include "Bridge.h"
#include <avr/io.h>

typedef struct {
	Object super;
	Bridge *bridge;
} InterruptHandler;


#define initInterruptHandler(bridge) { initObject(), bridge}
	
int input(InterruptHandler *self, int unUsed);

#endif