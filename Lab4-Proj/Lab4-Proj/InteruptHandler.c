#include <avr/io.h>
#include "InteruptHandler.h"
#include "Joystick.h"
#include "TinyTimber.h"



void Switch(InterruptHandler *self, int arg) {
	if (self->risingEdge){
		self->risingEdge = false;
		ASYNC(self->joystick, joyStickHorizontalControll, 0);		
	}else{
		self->risingEdge = true;
	}
}

void Change(InterruptHandler *self, int arg) {
	ASYNC(self->joystick, joyStickVerticalControll, 0);
}