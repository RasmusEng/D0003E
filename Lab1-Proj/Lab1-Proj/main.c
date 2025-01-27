/*
 * main.c
 *
 * Created: 1/23/2025 9:10:51 AM
 *  Author: Rasmus & Joel
 */ 

#include <xc.h>
#include "LCC-Driver.h"
#include <util/delay.h>
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
	for(long j = 2; j<sqrt(i); j++){
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

void blink(){
	TCCR1B |= (1 << CS12);
	
	uint16_t half = 32768;
	
	while(1){
		
		uint16_t current_time = TCNT1;
		
		LCDDR0 = 0x0;
		LCDDR1 = 0x0;
		LCDDR2 = 0x0;
		LCDDR3 = 0x0;
		while(TCNT1 != current_time + half){}
		
		uint16_t current_time2 = TCNT1;
		
		LCDDR0 = 0x1;
		LCDDR1 = 0x1;
		LCDDR2 = 0x1;
		LCDDR3 = 0x1;
		
		while(TCNT1 != current_time2 + half){}
	}
}

void button(){
	while(1){
		LCDDR0 = (LCDDR0 & 0x4) ? 0x00 : 0x4;
		while(PINB & (0x1<<PINB7));
		while(!(PINB & (0x1<<PINB7)));
	}
}

void blink4(){
	TCCR1B |= (1 << CS12);
	
	uint16_t half = 32768;

	uint16_t current_time = TCNT1;
		
	//LCDDR0 = 0x0;
	LCDDR2 &= ~(4 << 0); // Sl�ck segment f�r "1"
	while(TCNT1 != current_time + half){}
		
	uint16_t current_time2 = TCNT1;
		
	//LCDDR0 = 0x001;
	LCDDR2 |= (4 << 0); // T�nd segment f�r "1"
		
	while(TCNT1 != current_time2 + half){}
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
	while(1){
		primes4(&j);
		blink4();
		button4(&check);
	}
}

int main(void)
{
	CLK_init();
	LCD_Init();
	button_init();
	
	part4();
	
	//button();
	//blink();
	//primes(100);
	//writeLong(1000);
	//writeLong(10);
	/*for(char i = '0'; i <= '9'; i++){
		for(int j = 0; j <= 6; j++){
			writeChar(i,j);
			_delay_ms(1000);
		}
	}*/
	while(1){
	}
}
