#include "PulseGenerator.h"

int increase(PulseGenerator *self, int unused){
	if (!(self->currentFreq >= 99)){
		self->currentFreq += 1;
		ASYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	}
	return 0;
}

int decrease(PulseGenerator *self, int unused){
	if (self->currentFreq > 0) self->currentFreq -= 1;
	
	ASYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	
	return 0;
}

int reset(PulseGenerator *self, int unused){
	if (self->currentFreq == 0){
		self->currentFreq = self->lastFreq;
	}
	else{
		self->lastFreq = self->currentFreq;
		self->currentFreq = 0;
	}
	ASYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	
	return 0;
}

int generator(PulseGenerator *self, int unused){
	if(self->currentFreq > 0){ //Not zero
		ASYNC(self->outPut, sendSignal, self->pin);
		int fre = (500/self->currentFreq);
		AFTER(MSEC(fre), self, generator, 0);
	}else{ //Zeros
		ASYNC(self, setLow, self->pin);
		AFTER(MSEC(500), self, generator, 0);
	}

	return 0;
}