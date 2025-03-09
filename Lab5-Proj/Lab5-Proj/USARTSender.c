#include "USARTSender.h"
#include "TinyTimber.h"
#include <avr/io.h>

int sendSignal(USARTSender *self, int data){
	if(( UCSR0A & (1<<UDRE0))){
		UDR0 = data;
	}else{
		AFTER(MSEC(10), self, sendSignal, data); //MBY change time
	}
	return 0;
}