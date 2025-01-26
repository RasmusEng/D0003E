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
	LCDDR2 &= ~(4 << 0); // Släck segment för "1"
	while(TCNT1 != current_time + half){}
		
	uint16_t current_time2 = TCNT1;
		
	//LCDDR0 = 0x001;
	LCDDR2 |= (4 << 0); // Tänd segment för "1"
		
	while(TCNT1 != current_time2 + half){}
}


void primes4(long j){
	if (is_prime(j)){
		writeLong(j);
	}
}



void button4(int *check){
	if (PINB & (0x1<<PINB7) && *check)
	{
		
		LCDDR0 &= ~(4 << 0);;
		*check = 0;
	}
	else if(!(PINB & (0x1<<PINB7)))
	{
		
		LCDDR0 |= (4 << 0);
		*check = 1;
	}
}




void part4(){
	long j = 25000;
	int check = 1;
	while(1){
		primes4(j);
		blink4();
		button4(check);
		j += 1;
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
