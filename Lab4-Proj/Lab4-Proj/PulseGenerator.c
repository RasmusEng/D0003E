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
	/*if (self->currentFreq != 0){
		self->lastFreq = self->currentFreq;
		self->currentFreq = 0;
	}else{
		self->currentFreq = self->lastFreq;
	}*/
	if (self->currentFreq) {
		self->lastFreq = self->currentFreq;
		self->currentFreq = 0;
	} else {
		self->currentFreq = self->lastFreq;
	}
	//ASYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	ASYNC(self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	//AFTER(MSEC(20), self->display, printAt, PACK_PRINT(self->currentFreq, self->pos));
	
	return 0;
}

int generator(PulseGenerator *self, int unused){
	if(self->currentFreq != 0){ //Not zero
		self->High = !self->High;
		//int fre = (500/self->currentFreq);
		ASYNC(self->outPut, sendSignal, self->pin);
		AFTER(MSEC(500/self->currentFreq), self, generator, 0);
	}else{ //Zeros
		if(self->High){ //Replace with self->High for it to work
			ASYNC(self->outPut, setLow, self->pin);
		}
		AFTER(MSEC(500), self, generator, 0);
	}

	return 0;
}