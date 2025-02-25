#include "PulseGenerator.h"

int increase(PulseGenerator *self, int unused){
	if (!(self->currentFreq >= 99)) self->currentFreq += 1;
	SYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));

	if(self->currentFreq == 1){
		ASYNC(self, generator, 0); // Ändrat från SYNC till ASYNC
	}
	return 0;
}

int decrease(PulseGenerator *self, int unused){
	if (self->currentFreq == 1) ASYNC(self, setLow, self->pin);  // Ändrat från SYNC till ASYNC

	if (self->currentFreq > 0){
		self->currentFreq--;
		SYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	}

	return 0;
}

int reset(PulseGenerator *self, int unused){
	if (self->currentFreq == 0){
		self->currentFreq = self->lastFreq;
		if(self->currentFreq != 0) SYNC(self, generator, 0);
		}else{
		self->lastFreq = self->currentFreq;
		self->currentFreq = 0;
		SYNC(self, setLow, self->pin);
	}
	SYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	
	return 0;
}

int generator(PulseGenerator *self, int unused){
	if(self->currentFreq > 0){
		int fre = 500 / self->currentFreq;
		AFTER(MSEC(fre), self, generator, 0);
	}

	return 0;
}

