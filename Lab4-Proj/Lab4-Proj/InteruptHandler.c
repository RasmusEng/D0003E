#include "InteruptHandler.h"

int Switch(InterruptHandler *self, int arg) {
	/*if (self->risingEdge){
		self->risingEdge = false;
		ASYNC(self->joystick, joyStickHorizontalControll, 0);		
	}else{
		self->risingEdge = true;
	}*/
	//ASYNC(self->joystick, joyStickHorizontalControll, 0);
	AFTER(MSEC(50), self->joystick, joyStickHorizontalControll, 0);
}

int Change(InterruptHandler *self, int arg) {
	ASYNC(self->joystick, joyStickVerticalControll, 0);
}