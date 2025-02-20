/*
* Lab3-Proj.c
*
* Created: 2025-02-10 14:50:15
* Author : Joel & Rasmus
*/ 
#include "LCD_Driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include "N.h"
#include "TinyTimber.h"

N pulse1 = initN(1);
N pulse2 = initN(3);

void CLK_Init(){
	CLKPR = 0x80;
	CLKPR = 0x00;

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

void init(){
	CLK_Init();
	LCD_Init();
	BUTTON_Init();
	BUTTON_Int();
}

int main(void)
{    
	init();
	INSTALL();
	return TINYTIMBER();

}