#include "PulseController.h"

int sendSignal(PulseController *self, int pin){
	if(pin == 1){
		PORTE ^= (1 << PE4);
		}else if(pin == 3){
		PORTE ^= (1 << PE6);
	}
	return 0;
}

int setLow(PulseController *self, int pin){
	if(pin == 1){
		PORTE &= ~(0 << PE4); 
	}else if(pin == 3){
		PORTE &= ~(0 << PE6);
	}
	return 0;
}