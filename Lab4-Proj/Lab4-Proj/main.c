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

void CLK_Init(){
	// Timer
	DDRB = (1<<DDB7);
}

void BUTTON_Init(){
	PORTB |= (1 << 7);
}

void BUTTON_Int(){
	//Interrupt enables
	EIMSK  |= (0x1 << PCINT15);
	PCMSK1 |= (0x1 << PCINT15);
}

int main(void)
{    
	init();
	INSTALL(&gui, joyStickVerticalControll, IRQ_PCINT1);
	INSTALL(&gui, joyStickHorizontalControll, IRQ_PCINT0);
	return TINYTIMBER();

}