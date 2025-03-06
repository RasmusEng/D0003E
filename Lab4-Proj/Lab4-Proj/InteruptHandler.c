#include "InteruptHandler.h"

int Switch(InterruptHandler *self, int arg) {
	AFTER(MSEC(50), self->joystick, joyStickHorizontalControll, 0);
	return arg;
}

int Change(InterruptHandler *self, int arg) {
	ASYNC(self->joystick, joyStickVerticalControll, 0);
	return arg;
}