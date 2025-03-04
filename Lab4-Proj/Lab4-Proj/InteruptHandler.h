#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "Joystick.h"
#include "InteruptHandler.h"

typedef struct {
	Object super;
	Joystick *joystick;
	bool risingEdge;
} InterruptHandler;

void Switch(InterruptHandler *self, int arg);
void Change(InterruptHandler *self, int arg);

#define initInterruptHandler(js) { initObject(), js, false}

#endif /* INTERRUPTHANDLER_H_ */