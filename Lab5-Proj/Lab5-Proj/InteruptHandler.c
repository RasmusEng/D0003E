#include "InteruptHandler.h"

int input(InterruptHandler *self, int __attribute__((unused)) unUsed) {
	ASYNC(self->bridge, handleInput, UDR0);
	return 0;
}
