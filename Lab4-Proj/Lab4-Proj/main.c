/*
* Lab3-Proj.c
*
* Created: 2025-02-10 14:50:15
* Author : Joel & Rasmus
*/ 
#include "PulseGenerator.h"
#include "TinyTimber.h"
#include "INIT.h"

//mby move to main?
PulseGenerator pulseLeft = initPulseGenerator(1);
PulseGenerator pulseRight = initPulseGenerator(3);
GUI gui = initGUI(pulseLeft, pulseRight);

int main(void)
{    
	INIT();
	INSTALL(&gui, joyStickVerticalControll, IRQ_PCINT1);
	INSTALL(&gui, joyStickHorizontalControll, IRQ_PCINT0);
	return TINYTIMBER();'
}