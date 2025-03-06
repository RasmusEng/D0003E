#ifndef PulseController_h
#define PulseController_h

#include <stdint.h>
#include <avr/io.h>
#include "PulseController.h"
#include "TinyTimber.h"
#include "LCD_Driver.h"

typedef struct
{
	Object super;
} PulseController;

#define initPulseController() {initObject()};
int sendSignal(PulseController *self, int);
int setLow(PulseController *self, int pin);


#endif