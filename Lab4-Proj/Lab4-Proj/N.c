#include "N.h"

uint16_t increase(N *self){
    if (self->currentFreq >= 99) return self->currentFreq;
    self->currentFreq += 1;
    return self->currentFreq;
}

uint16_t decrease(N *self){
    if (self->currentFreq == 0) return self->currentFreq;
    self->currentFreq -= 1;
    return self->currentFreq;
}

uint16_t reset(N *self){
    if(self->currentFreq == 0) self->currentFreq = self->lastFreq;
    else self->currentFreq = 0;
    return self->currentFreq;
}

