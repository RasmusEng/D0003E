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
#include "JoystickInter.h"


int main(void)
{    
	INIT();
	PulseController pulseController = initPulseController();
	LCD_Driver display = initLCD_Driver();
	PulseGenerator pulseLeft = initPulseGenerator(0, 1, 1, &pulseController, &display);
	PulseGenerator pulseRight = initPulseGenerator(0, 4, 3, &pulseController, &display);
	GUI gui = initGUI(&pulseLeft, &pulseRight);
	JoystickInter joy = initJoystickInter(&gui);
	//ASYNC(&display, printAt, PACK_PRINT(pulseLeft.currentFreq, pulseLeft.pos));
	//ASYNC(&display, printAt, PACK_PRINT(pulseRight.currentFreq, pulseRight.pos));
	INSTALL(&joy, joyStickVerticalControll, IRQ_PCINT1);
	INSTALL(&joy, joyStickHorizontalControll, IRQ_PCINT0);
	return TINYTIMBER(NULL, NULL, NULL);
}