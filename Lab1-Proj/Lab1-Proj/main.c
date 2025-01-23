/*
 * main.c
 *
 * Created: 1/23/2025 9:10:51 AM
 *  Author: joel
 */ 

#include <xc.h>
//#include <LCC-Driver.h>

int main(void)
{
	void CLK_init(void){
		CLKPR = 0x80;
		CLKPR = 0x00;
	}
	
    LCD_Init();
	writeChar(27, 0);
	
}