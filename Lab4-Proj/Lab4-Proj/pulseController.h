#ifndef PulseController_h
#define PulseController_h

#include <stdint.h>
#include "TinyTimber.h"

typedef struct
{
	Object super;
} PulseController;

#define initPulseController() {initObject()};
void sendSignal(PulseController *self, int);


#endif