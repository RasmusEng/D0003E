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
	PulseGenerator *pulseLeft = initPulseGenerator(50, 1, 1, 1);
	PulseGenerator *pulseRight = initPulseGenerator(50, 3, 4, 1);
	GUI gui = initGUI(pulseLeft, pulseRight);
	INIT();
	INSTALL(&gui, joyStickVerticalControll, IRQ_PCINT1);
	INSTALL(&gui, joyStickHorizontalControll, IRQ_PCINT0);
	return TINYTIMBER(NULL, NULL, NULL);
}