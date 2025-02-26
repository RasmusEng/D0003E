#include "Joystick.h"
#include <avr/io.h>
#include "GUI.h"

int holdJoyStick(Joystick *self, int unUsed) {
	if (!(PINB & (1 << PB7))) { // DOWN
		ASYNC(self->gui, freqDown, 0); // SYNC till ASYNC
		AFTER(MSEC(500), self, holdJoyStick, 0);
	}
	if (!(PINB & (1 << PB6))) { // UP
		ASYNC(self->gui, freqUp, 0); // SYNC till ASYNC
		AFTER(MSEC(500), self, holdJoyStick, 0);
	}
	return 0;
}

int joyStickHorizontalControll(Joystick *self, int unUsed){
	if((!(PINE & (1 << PE1)) || !(PINE & (1 << PE6)))){
		AFTER(MSEC(200), self->gui, switchState, 0);
	}
	return 0;
}

int joyStickVerticalControll(Joystick *self, int unUsed){
	if (!(PINB & (1 << PB7))) { //DOWN
		//ASYNC(self, freqDown, 0);
		AFTER(MSEC(50), self, holdJoyStick, 0);
	}
	if (!(PINB & (1 << PB6))) { //UP
		//ASYNC(self, freqUp, 0);
		AFTER(MSEC(50), self, holdJoyStick, 0);
		
	}
	if (!(PINB & (1 << PB4))) { //PRESS
		//ASYNC(self, press, 0);
		AFTER(MSEC(50), self, press, 0);
	}
	return 0;
}


