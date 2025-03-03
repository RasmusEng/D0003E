#ifndef JoystickInter_H
#define JoystickInter_H

#include "TinyTimber.h"
#include "GUI.h"
#include <stdbool.h>

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