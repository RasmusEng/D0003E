/*
 * Lab3-Proj.c
 *
 * Created: 2025-02-10 14:50:15
 * Author : Joel & Rasmus
 */ 

#include "tinythreads.h"
#include "LCD_Driver.h"
#include <avr/io.h>
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

void init(){
    CLK_Init();
    LCD_Init();
    BUTTON_Init();
	
    
}

//mutex  mutex_PePe =  MUTEX_INIT;
void printAt(long num, int pos) {
	//lock(&mutex_PePe);
	int pp;
	pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	int j = 0;
	for(int i = 0; i < 1000; i++){
		j++;
	}
	pp++;
	writeChar( num % 10 + '0', pp);
	//unlock(&mutex_PePe);
}

//static volatile long  buttCount = 0;

void button(){
	long  buttCount = 0;
	while(1){
		printAt(buttCount, 3);
		while(!(PINB & (0x1<<PINB7)));
		while(PINB & (0x1<<PINB7));
		buttCount = buttCount + 1;
	}
}

void blink(){
    TCCR1B |= (1 << CS12);
    
    while(1){
        while (getCount() < 10){
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




int main(void)
{    
    init();
    /* Replace with your application code */
	
    //spawn(computePrimes, 0);
	//button();
	spawn(button, 0);
	computePrimes(0);
	
    //spawn(blink, 0);
    
}