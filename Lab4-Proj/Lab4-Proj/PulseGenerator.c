#include "PulseGenerator.h"

uint16_t increase(PulseGenerator *self){
    if (self->currentFreq >= 99) return self->currentFreq;
    self->currentFreq += 1;
    return self->currentFreq;
}

uint16_t decrease(PulseGenerator *self){
    if (self->currentFreq == 0) return self->currentFreq;
    self->currentFreq -= 1;
    return self->currentFreq;
}

uint16_t reset(PulseGenerator *self){
    if(self->currentFreq == 0) self->currentFreq = self->lastFreq;
    else self->currentFreq = 0;
    return self->currentFreq;
}

