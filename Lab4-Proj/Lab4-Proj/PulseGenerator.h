#ifndef PulseGenerator_H
#define PulseGenerator_H
#include "TinyTimber.h"
#include <stdint.h>

typedef struct
{
    Object super;
    uint16_t currentFreq;
    uint16_t lastFreq;
    int pos;
    int pin;
} pulseGenerator;

// Oklart om vi sätter lastfreq till currentFreq här
#define initPulseGenerator(currentFreq, pos, pin) {initObject(), currentFreq, currentFreq, pos, pin}

uint16_t increase(PulseGenerator *self);
uint16_t decrease(PulseGenerator *self);
uint16_t reset(PulseGenerator *self);

#endif