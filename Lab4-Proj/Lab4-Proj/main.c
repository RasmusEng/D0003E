/*
* Lab3-Proj.c
*
* Created: 2025-02-10 14:50:15
* Author : Joel & Rasmus
*/ 
#include "PulseGenerator.h"
#include "TinyTimber.h"
#include "INIT.h"
#include "GUI.h"
#include "LCD_Driver.h"
#include "Joystick.h"
#include "InteruptHandler.h"



int main(void)
{    
	INIT();
	PulseController pulseController = initPulseController();
	LCD_Driver display = initLCD_Driver();
	PulseGenerator pulseLeft = initPulseGenerator(0, 1, 1, &pulseController, &display);
	PulseGenerator pulseRight = initPulseGenerator(0, 4, 3, &pulseController, &display);
	GUI gui = initGUI(&pulseLeft, &pulseRight);
	Joystick joy = initJoystick(&gui);
	INIT_PULSE_GEN(&pulseLeft, &pulseRight);
	InterruptHandler inter = initInterruptHandler(&joy);
	INSTALL(&inter, Switch, IRQ_PCINT0);
	INSTALL(&inter, Change, IRQ_PCINT1);
	return TINYTIMBER(NULL, NULL, NULL);
}