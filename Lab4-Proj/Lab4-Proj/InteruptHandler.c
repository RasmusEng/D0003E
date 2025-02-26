#include <avr/io.h>
#include "InteruptHandler.h"
#include "Joystick.h"
#include "TinyTimber.h"


void Switch(InterruptHandler *self, int arg) {
	ASYNC(self->joystick, joyStickHorizontalControll(), 0);
}

/* Interrupt function for changing the active pulse generator frequency */
void Change(InterruptHandler *self, int arg) {
	ASYNC(self->joystick, joyStickVerticalControll, 0);
}