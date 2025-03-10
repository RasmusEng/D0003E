/*
* LCD_Driver.c
*
*  Author: Joel & Rasmus
*/

#include "LCD_Driver.h"
#include <avr/io.h>
#include <stdbool.h>

static unsigned char charCodes[10][4] = {
	{0x1,0x5,0x5,0x1}, // 0
	{0x0,0x8,0x0,0x2}, // 1
	{0x1,0x1,0xE,0x1}, // 2
	{0x1,0x1,0xB,0x1}, // 3
	{0x0,0x5,0xB,0x0}, // 4
	{0x1,0x4,0xB,0x1}, // 5
	{0x0,0x4,0xF,0x1}, // 6
	{0x1,0x1,0x9,0x0}, // 7
	{0x1,0x5,0xF,0x1}, // 8
	{0x1,0x5,0xB,0x0}, // 9
};

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
}

void LCD_update(unsigned char data1, unsigned char data2){
	/* LCD Blanking and Low power waveform are unchanged. */
	/* Update Display memory. */
	LCDDR0 = data1;
	LCDDR6 = data2;
}

unsigned char offsetPos[8] = {
	/*THis list is used to offset positions of characters for the display */
	0,0,1,1,2,2,3,3
};


void writeChar(char ch, int pos){
	/* Returns if given input is not possible to print */
	if(pos < 0 || pos > 5 || ch < 48 || ch > 57){
		return;
	}
	volatile uint8_t *lcd_base = &LCDDR0 + offsetPos[pos];
	
	int number = (int)ch - 48;
	int shift = 0;
	/*Clears the part of the display we want to write onto */
	if (pos % 2 == 1){
		shift = 4;
		lcd_base[0]  = lcd_base[0]  & 0x0F;
		lcd_base[5]  = lcd_base[5]  & 0x0F;
		lcd_base[10] = lcd_base[10] & 0x0F;
		lcd_base[15] = lcd_base[15] & 0x0F;
		}else{
		lcd_base[0]  = lcd_base[0]  & 0xF0;
		lcd_base[5]  = lcd_base[5]  & 0xF0;
		lcd_base[10] = lcd_base[10] & 0xF0;
		lcd_base[15] = lcd_base[15] & 0xF0;
	}
	/*Writes to the display*/
	lcd_base[0]  = charCodes[number][0]<<shift | lcd_base[0] ;
	lcd_base[5]  = charCodes[number][1]<<shift | lcd_base[5] ;
	lcd_base[10] = charCodes[number][2]<<shift | lcd_base[10];
	lcd_base[15] = charCodes[number][3]<<shift | lcd_base[15];
}

void writeLong(long i){
	/* Writes the 6 least significant numbers of a long */
	if(i == 0){
		writeChar('0', 6);
		return;
	}
	char chars[7];
	
	for(int j = 5; j>-1; j--){
		chars[j] = (char)(i%10)+48;
		i /= 10;
	}
	
	bool importantNum = false;
	for(int j = 6; j>-1; j--){
		if(!importantNum){
			if(chars[j] == 0){
				continue;
				}else{
				importantNum = true;
			}
		}
		writeChar(chars[j],j);
	}
}