#include "USARTSender.h"
#include "TinyTimber.h"
#include <avr/io.h>

int sendSignal(USARTSender *self, int data){
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
	return 0;
}