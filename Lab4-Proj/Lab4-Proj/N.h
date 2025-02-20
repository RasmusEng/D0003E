#ifndef N_H
#define N_H
#include "TinyTimber.h"
#include <stdint.h>

typedef struct
{
    Object super;
    uint16_t currentFreq;
    uint16_t lastFreq;
    int pos;
} N;

// Oklart om vi sätter lastfreq till currentFreq här
#define initN(currentFreq, pos) {initObject(), currentFreq, currentFreq, pos}

uint16_t increase(N *self);
uint16_t decrease(N *self);
uint16_t reset(N *self);

#endif