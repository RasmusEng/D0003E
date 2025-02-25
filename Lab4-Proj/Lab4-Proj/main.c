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


int main(void)
{    
	INIT();
	PulseController pulseController = initPulseController();
	LCD_Driver display = initLCD_Driver();
	PulseGenerator pulseLeft = initPulseGenerator(0, 1, 1, &pulseController, &display);
	PulseGenerator pulseRight = initPulseGenerator(0, 4, 3, &pulseController, &display);
	GUI gui = initGUI(&pulseLeft, &pulseRight);
	INSTALL(&gui, joyStickVerticalControll, IRQ_PCINT1);
	INSTALL(&gui, joyStickHorizontalControll, IRQ_PCINT0);
	return TINYTIMBER(NULL, NULL, NULL);
}