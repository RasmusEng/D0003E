#ifndef USARTSENDER_H_
#define USARTSENDER_H_

#include "TinyTimber.h"

typedef struct  
{
	Object super;
} USARTSender;

#define initUSARTSender() {initObject()}

int sendSignal(USARTSender *self, int data);

#endif /* USARTSENDER_H_ */