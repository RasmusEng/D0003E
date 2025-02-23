#include "PulseGenerator.h"

int increase(PulseGenerator *self, int unused){
    if (!(self->currentFreq >= 99)) self->currentFreq += 1;
	printAt(self->currentFreq, self->pos);
	return self->currentFreq;
}

int decrease(PulseGenerator *self, int unused){
    if (!(self->currentFreq == 0)) self->currentFreq -= 1;
	printAt(self->currentFreq, self->pos);
	
	return self->currentFreq;
}

int reset(PulseGenerator *self, int unused){
    if (self->currentFreq == 0) self->currentFreq = self->lastFreq;
    else self->currentFreq = 0;
	printAt(self->currentFreq, self->pos);
	
	return self->currentFreq;
}

int generator(PulseGenerator *self, int unused){
	//TODO fix this sheit
	return 0;
}

