/*
 * main.c
 *
 * Created: 1/23/2025 9:10:51 AM
 *  Author: Rasmus & Joel
 */ 

#include <xc.h>
#include "LCD_Driver.h"
#include <stdbool.h>

void CLK_init(void){
	CLKPR = 0x80;
	CLKPR = 0x00;
}

void button_init(void){
	PORTB |= (1 << 7);
	DDRB = (1<<DDB7);
}

bool is_prime(long i){
	for(long j = 2; j<i; j++){
		if (i % j == 0){
			return false;
		}
	}
	return true;
}

void primes(long j){
	for(long i =2; i <= j; i++){
		if (is_prime(i)){
			writeLong(i);
		}
	}
}

void blink2(){
	TCCR1B |= (1 << CS12);
	
	int16_t nextBlink= 15625;
	int16_t acc = 0;
	int16_t last = 0;
	int16_t diff = 0;
	while(1){
		int16_t current = TCNT1;
		if (current >= last) {
			diff = current - last;
			} else {
			diff = (65535 - last) + current + 1;
		}
		acc += diff;
		last = current;
		if (acc >= nextBlink){
			LCDDR18 ^= 1;
			acc -= nextBlink;
			return;
		}
	}
}

void button(){
	while(1){
		LCDDR0 = (LCDDR0 & 0x4) ? 0x00 : 0x4;
		PORTE ^= (0x1 << PE4);
		while(!(PINB & (0x1<<PINB7)));
		while(PINB & (0x1<<PINB7));
	}
}

void primes4(long *j){
	while(1){
		bool check = is_prime(*j);
		
		if(check){
			writeLong(*j);
			*j += 2;	
			return;
		}else{
			*j += 2;
		}
	}
}

void button4(bool *check){
	if (PINB & (0x1<<PINB7)){
		*check = false;
	}else if(check){
		LCDDR13 ^=  1;
		*check = false;
	}
}

void part4(){
	long j = 25001;
	bool check = false;
	DDRE |= (1 << DDE4) | (1 << DDE6);
	while(1){
		//PORTE ^= (0x1 << PE4);
		PORTE = (1 << PE4) | (1 << PE6);
		for(int i = 0; i<1000000; i++){
			
		}
		PORTE = ((0 << PE4) | (0 << PE6));
	}
}

void test(){
	//DDRE |= (1 << DDE4) | (1 << DDE6);

	while(1) {
		// Set PE4 and PE6 HIGH
		//PORTE |= (1 << PE4) | (1 << PE6);
		PORTE ^= (1 << PE4);

		// Delay loop
		for (volatile long i = 0; i < 10000; i++) { }

		// Set PE4 and PE6 LOW properly
		//PORTE &= ~((1 << PE4) | (1 << PE6));
		PORTE ^= (1 << PE6);
		// Delay loop
		for (volatile long i = 0; i < 10000; i++) { }

	}
}

int main(void)
{
	CLK_init();
	LCD_Init();
	button_init();
	
	//primes(25000
	//blink2();
	//button(););
	//part4();
	test();
	//writeLong(123456789);
	//writeLong(10);
	while(1){
	}
}
