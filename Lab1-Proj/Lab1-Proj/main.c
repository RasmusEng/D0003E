/*
 * main.c
 *
 * Created: 1/23/2025 9:10:51 AM
 *  Author: Rasmus & Joel
 */ 

#include <xc.h>
#include "LCC-Driver.h"
#include <util/delay.h>

void CLK_init(void){
	CLKPR = 0x80;
	CLKPR = 0x00;
}

int main(void)
{
	CLK_init();
	LCD_Init();
	
	for(char i = '0'; i <= '9'; i++){
		for(int j = 0; j <= 6; j++){
			writeChar(i,j);
			_delay_ms(1000);
		}
	}
	while(1){
	}
}