#ifndef PulseGenerator_H
#define PulseGenerator_H

#include <stdint.h>
#include "PulseController.h"
#include "TinyTimber.h"
#include "LCD_Driver.h"

typedef struct
{
    Object super;
    int currentFreq;
    int lastFreq;
    int pos;
    int pin;
    PulseController *outPut;
	LCD_Driver *display;
	int High;
} PulseGenerator;

#define initPulseGenerator(currentFreq, pos, pin, outPut, display) {initObject(), currentFreq, 0, pos, pin, outPut, display, 0}

int increase(PulseGenerator *self, int);
int decrease(PulseGenerator *self, int);
int reset(PulseGenerator *self, int);
int generator(PulseGenerator *self, int);

#endif