#ifndef PulseGenerator_H
#define PulseGenerator_H
#include "TinyTimber.h"
#include "PulseController.h"
#include "LCD_Driver.h"
#include <stdint.h>

typedef struct
{
    Object super;
    int currentFreq;
    int lastFreq;
    int pos;
    int pin;
    PulseController *outPut;
	LCD_Driver *display;
} PulseGenerator;

#define initPulseGenerator(currentFreq, pos, pin, outPut, display) {initObject(), currentFreq, currentFreq, pos, pin, outPut, display}

int increase(PulseGenerator *self, int);
int decrease(PulseGenerator *self, int);
int reset(PulseGenerator *self, int);
int generator(PulseGenerator *self, int);

#endif