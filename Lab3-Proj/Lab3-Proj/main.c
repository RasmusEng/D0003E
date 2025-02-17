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
mutex buttonMut = MUTEX_INIT;
mutex primesMut = MUTEX_INIT;
mutex blinkMut = MUTEX_INIT;

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
}

void init(){
	CLK_Init();
	LCD_Init();
	BUTTON_Init();
	BUTTON_Int();
}

void printAt(long num, int pos) {
	int pp;
	pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	int j = 0;
	for(int i = 0; i < 1000; i++){
		j++;
	}
	pp++;
	writeChar( num % 10 + '0', pp);
}

void button(){
	long  buttCount = 0;
	while(1){
		printAt(buttCount, 3);
		buttCount = buttCount + 1;
	}
}

void blink(){
	TCCR1B |= (1 << CS12);

	while(1){
		while (getCount() < 3){
		}
		LCDDR18 ^= 1;
		resetCount();
	}
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
	for(n = 1; ; n++) {
		if (is_prime(n)) {
			printAt(n, pos);
		}
	}
}

ISR(PCINT1_vect){
	unlock(&buttonMut);
    if(!(PINB & (0x1<<PINB7))){
        yield();
    }
	lock(&buttonMut);
}

ISR(TIMER1_COMPA_vect){
	unlock(&blinkMut);
	addCount();
    yield();
	lock(&blinkMut);
}	

int main(void)
{    
	init();
	
	spawn(blink, 0);
	spawn(button, 0);
	computePrimes(0);
	
}