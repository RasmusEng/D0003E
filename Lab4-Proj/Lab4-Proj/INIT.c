#include "LCD_Driver.h"
#include <avr/io.h>
#include <stdbool.h>

void CPUCLK_Init(void){
	CLKPR = 0x80;
	CLKPR = 0x00;
}

void LCD_Init(void){
	//Use 32 kHz crystal oscillator
	//1/3 Bias and 1/4 duty, SEG0:SEG24 is used as port pins
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX0)| (1<<LCDMUX1)|(1<<LCDPM0) |(1<<LCDPM1) |(1<<LCDPM2);
	/* Using 16 as prescaler selection and 8 as LCD Clock Divide */
	/* gives a frame rate of 32 Hz */
	LCDFRR = (1<<LCDCD0) | (1<<LCDCD1) | (1<<LCDCD2);
	/* Set segment drive time to 300 μs and output voltage to 3.35 V*/
	LCDCCR = (1<<LCDDC0) | (1<<LCDCC1) | (1<<LCDCC2) | (1<<LCDCC3);
	/* Enable LCD, low power waveform and no interrupt enabled */
	LCDCRA = (1<<LCDEN);

	//Indicator bits 
	LCDDR13 ^= 1;
}

void CLK_Init(){
	// Timer
	DDRB = (1<<DDB7);
}

void BUTTON_Init(){
	PORTB |= (1 << 7) | (1 << 6) | (1 << 4);
	PORTE |= (1 << 3) | (1 << 2);


    //Interrupt enables
	EIMSK  |= (1 << PCIE1) | (1 << PCIE0);
	PCMSK1 |= (1 << PCINT11) | (1 << PCINT12) | (1 << PCINT13) | (1 << PCINT14) | (1 << PCINT15);
	
	PCMSK0 |= (1 << PCINT2) | (1 << PCINT3);
}

void INIT(){
	CPUCLK_Init();
	LCD_Init();
	CLK_Init();
	BUTTON_Init();
}