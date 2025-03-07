#include "InteruptHandler.h"

int Switch(InterruptHandler *self, int arg) {
	ASYNC(self->joystick, joyStickHorizontalControll, PINE);
	return arg;
}

int Change(InterruptHandler *self, int arg) {
	ASYNC(self->joystick, joyStickVerticalControll, 0);
	return arg;
}