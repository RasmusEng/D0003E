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

mutex  mutex_PePe =  MUTEX_INIT;
void printAt(long num, int pos) {
	//lock(&mutex_PePe);
	int pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	int j = 0;
	for(int i = 0; i < 1000; i++){
		j++;
	}
	pp++;
	writeChar( num % 10 + '0', pp);
	//unlock(&mutex_PePe);
}

int main(void)
{	
	init()
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

