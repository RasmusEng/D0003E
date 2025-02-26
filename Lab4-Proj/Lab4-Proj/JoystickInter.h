/*
 * IncFile1.h
 *
 * Created: 2025-02-26 14:13:52
 *  Author: raseng-3
 */ 


#ifndef JoystickInter_H
#define JoystickInter_H

#include "TinyTimber.h"
#include "GUI.h"

typedef struct
{
	Object super;
	GUI *gui;
} JoystickInter;

#define initJoystickInter(gui) {initObject(), gui};

int joyStickHorizontalControll();
int joyStickVerticalControll();

#endif JoystickInter_H