#include "Joystick.h"
#include <avr/io.h>
#include "GUI.h"

int holdJoyStick(Joystick *self, int unUsed) {
	if (!(PINB & (1 << PB7))) { // DOWN
		ASYNC(self->gui, freqDown, 0); // SYNC till ASYNC
		AFTER(MSEC(50), self, holdJoyStick, 0);
	}
	if (!(PINB & (1 << PB6))) { // UP
		ASYNC(self->gui, freqUp, 0); // SYNC till ASYNC
		AFTER(MSEC(50), self, holdJoyStick, 0);
	}
	return 0;
}

int joyStickHorizontalControll(Joystick *self, int unUsed){
	if((!(PINE & (1 << PE1)) | !(PINE & (1 << PE6)))){
		ASYNC(self->gui, switchState,0);
	}
	return 0;
}

int joyStickVerticalControll(Joystick *self, int unUsed){
	if (!(PINB & (1 << PB7))) { //DOWN
		//ASYNC(self, holdJoyStick, 0);
		ASYNC(self->gui, freqDown, 0);
		
	}
	if (!(PINB & (1 << PB6))) { //UP
		//ASYNC(self, holdJoyStick, 0);
		ASYNC(self->gui, freqUp, 0);
	}
	if (!(PINB & (1 << PB4))) { //PRESS
		if (self->risingEdge){
			self->risingEdge = false;
			ASYNC(self->gui, press, 0);	
		}else{
			self->risingEdge = true;
		}
	}
	return 0;
}


