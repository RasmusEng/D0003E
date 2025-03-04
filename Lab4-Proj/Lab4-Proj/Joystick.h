#ifndef JoystickInter_H
#define JoystickInter_H

#include <stdbool.h>
#include <avr/io.h>
#include "TinyTimber.h"
#include "Joystick.h"
#include "GUI.h"

typedef struct
{
	Object super;
	GUI *gui;
	bool risingEdge;
	bool held;
} Joystick;

#define initJoystick(gui) {initObject(), gui};

int joyStickHorizontalControll(Joystick *self, int unUsed);
int joyStickVerticalControll(Joystick *self, int unUsed);

#endif