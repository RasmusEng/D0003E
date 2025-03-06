#include "Joystick.h"

int holdJoyStick(Joystick *self, int unUsed) {
	if (!(PINB & (1 << PB7))) { // DOWN
		self->held = true;
		ASYNC(self->gui, freqDown, 0);
		AFTER(MSEC(250), self, holdJoyStick, 0);
	}
	if (!(PINB & (1 << PB6))) { // UP
		self->held = true;
		ASYNC(self->gui, freqUp, 0); 
		AFTER(MSEC(250), self, holdJoyStick, 0);
	}
	self->held = false;
	return 0;
}

int joyStickHorizontalControll(Joystick *self, int unUsed){
	if((!(PINE & (1 << PE3)))){
		ASYNC(self->gui, switchState,0);
	}else if((!(PINE & (1 << PE6)))){
		ASYNC(self->gui, switchState,0);
	}
	return 0;
}

int joyStickVerticalControll(Joystick *self, int unUsed){
	if(!self->held){
	if (!(PINB & (1 << PB7))) { //DOWN
		ASYNC(self, holdJoyStick, 0);
		
	}
	if (!(PINB & (1 << PB6))) { //UP
		ASYNC(self, holdJoyStick, 0);
	}
	if (!(PINB & (1 << PB4))) { //PRESS
		if (self->risingEdge){
			self->risingEdge = false;
			ASYNC(self->gui, press, 0);	
		}else{
			self->risingEdge = true;
		}
	}
	}
	return 0;
}


