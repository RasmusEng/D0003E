#include "TinyTimber.h"
#include "Joystick.h"
#include <stdbool.h>

#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_


typedef struct {
	Object super;
} InterruptHandler;


#define initInterruptHandler() { initObject()}

#endif /* INTERRUPTHANDLER_H_ */