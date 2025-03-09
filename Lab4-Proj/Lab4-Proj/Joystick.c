#include "Joystick.h"

int holdJoyStick(Joystick *self, int unUsed) {
	if (!(PINB & (1 << PB7))) { // DOWN
		self->held = true;
		ASYNC(self->gui, freqDown, 0);
		AFTER(MSEC(100), self, holdJoyStick, 0);
	}
	if (!(PINB & (1 << PB6))) { // UP
		self->held = true;
		ASYNC(self->gui, freqUp, 0); 
		AFTER(MSEC(100), self, holdJoyStick, 0);
	}
	self->held = false;
	return 0;
}

int joyStickHorizontalControll(Joystick *self, int Used){
	if((!(Used & (1 << PE3)))){
		ASYNC(self->gui, switchState,0);
	}else if((!(Used & (1 << PE4)))){
		ASYNC(self->gui, switchState,0);
	}
	return 0;
}

int joyStickVerticalControll(Joystick *self, int unUsed){
	if(!self->held){
		if (!(PINB & (1 << PB7))) { //DOWN
			//self->held = true;
			AFTER(MSEC(50), self, holdJoyStick, 0);
		
		}
		if (!(PINB & (1 << PB6))) { //UP
			//self->held = true;
			AFTER(MSEC(50), self, holdJoyStick, 0);
		}
	}
		if (!(PINB & (1 << PB4))) { //PRESS
			if (self->risingEdge){
				self->risingEdge = false;
				ASYNC(self->gui, press, 0);
				//AFTER(MSEC(200), self->gui,press, 0);
			}else{
				self->risingEdge = true;
			}
			//ASYNC(self->gui, press, 0);
		}
	return 0;
}


