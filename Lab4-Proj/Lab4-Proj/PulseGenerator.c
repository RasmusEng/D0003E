#include "PulseGenerator.h"

int increase(PulseGenerator *self, int unused){
    if (self->currentFreq >= 99) return self->currentFreq;
    self->currentFreq += 1;
    return self->currentFreq;
}

int decrease(PulseGenerator *self, int unused){
    if (self->currentFreq == 0) return self->currentFreq;
    self->currentFreq -= 1;
    return self->currentFreq;
}

int reset(PulseGenerator *self, int unused){
    if(self->currentFreq == 0) self->currentFreq = self->lastFreq;
    else self->currentFreq = 0;
    return self->currentFreq;
}

int generator(PulseGenerator *self, int unused){
	//TODO fix this sheit
	return 0;
}

