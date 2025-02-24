#include "PulseGenerator.h"

int increase(PulseGenerator *self, int unused){
	if (!(self->currentFreq >= 99)) self->currentFreq += 1;
	ASYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	if(self->currentFreq == 1){
		ASYNC(self, generator, 0);
	}
	return self->currentFreq;
}

int decrease(PulseGenerator *self, int unused){
	if (!(self->currentFreq == 0)) self->currentFreq -= 1;
	ASYNC(self, setLow, self->pin);
	ASYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	
	return self->currentFreq;
}

int reset(PulseGenerator *self, int unused){
	if (self->currentFreq == 0){
		self->currentFreq = self->lastFreq;
		if(self->currentFreq != 0) ASYNC(self, generator, 0);
		}else{
		self->lastFreq = self->currentFreq;
		self->currentFreq = 0;
		ASYNC(self, setLow, self->pin);
	}
	ASYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	
	return self->currentFreq;
}

int generator(PulseGenerator *self, int unused){
	if(self->currentFreq){
		ASYNC(self->outPut, sendSignal, self->pin);
		int fre = (500/self->currentFreq);
		AFTER(MSEC(fre), self, generator, 0);
	}

	return 0;
}

