#ifndef PulseController_h
#define PulseController_h

#include <stdint.h>
#include "TinyTimber.h"

typedef struct
{
	Object super;
} PulseController;

#define initPulseController() {initObject()};
int sendSignal(PulseController *self, int);
int setLow(PulseController *self, int pin);


#endif