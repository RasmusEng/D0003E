/*
* Lab3-Proj.c
*
* Created: 2025-02-10 14:50:15
* Author : Joel & Rasmus
*/ 

#include "tinythreads.h"
#include "LCD_Driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
void CLK_Init(){
	CLKPR = 0x80;
	CLKPR = 0x00;
}

void BUTTON_Init(){
	PORTB |= (1 << 7);
	DDRB = (1<<DDB7);

} 

void BUTTON_Int(){
	//Interrupt enables
	EIMSK  |= (0x1 << PCINT15);
	PCMSK1 |= (0x1 << PCINT15);
	TCCR1B |= (1 << CS12);
}

void init(){
	CLK_Init();
	LCD_Init();
	BUTTON_Init();
	BUTTON_Int();
	timerInit();
}

void printAt(long num, int pos) {
	int pp;
	pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}

static	uint16_t presses = 0;
void button(){
	if (!(PINB & (1<<PINB7))) {
		printAt(++presses, 3);
	}
}

void blink(){
	LCDDR18 ^= 1;	
}

bool is_prime(long i){
	for(long j = 2; j<i; j++){
		if (i % j == 0){
			return false;
		}
	}
	return true;
}

void computePrimes(int pos) {
	/*Goes through and calculates prime numbers*/
	long n;
	for(n = 0; ; n++) {
		if (is_prime(n)) {
			printAt(n, pos);
		}
	}
	
}

ISR(PCINT1_vect){
	spawn(button, 0);
}

ISR(TIMER1_COMPA_vect){
	spawn(blink, 0);
}	

int main(void)
{    	
	//Lab3Alt3
	init();
	computePrimes(0);
}
