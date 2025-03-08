#include <avr/io.h>
#include "InteruptHandler.h"
#include "Joystick.h"
#include "TinyTimber.h"


void Input(InterruptHandler *self, int unUsed) {
	ASYNC(self->joystick, joyStickVerticalControll, 0);
}