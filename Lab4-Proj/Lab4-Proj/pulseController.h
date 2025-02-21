#ifndef pulseController_h
#define pulseController_h

#include <stdint.h>
#include "TinyTimber.h"

typedef struct
{
	Object super;
} PulseController;

#define initpulseController() {initObject()};
void sendSignal(PulseController *self, int);


#endif