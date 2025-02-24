#include "PulseController.h"
#include <avr/io.h>
#include "LCD_Driver.h"

int sendSignal(PulseController *self, int pin){
    if(pin == 1){
        PORTE ^= (1 << PE4);
    }else if(pin == 3){
        PORTE ^= (1 << PE6);
    }
	//printAt(PING, 3);
	
	//PORTE ^= (1 << PE4);
	/*for(int i = 0; i < 1000; i++){
		PORTE = (0 << PE4);
	}*/
	LCDDR18 ^= 1;
	return 0;
}