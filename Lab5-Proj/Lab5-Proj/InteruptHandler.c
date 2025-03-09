#include "InteruptHandler.h"

int input(InterruptHandler *self, int __attribute__((unused)) unUsed) {
	ASYNC(self->bridge, handelInput, UDR0);
	return 0;
}
