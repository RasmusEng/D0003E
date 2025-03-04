/*
* LCD_Driver.c
*
*  Author: Joel & Rasmus
*/
#include <avr/io.h>
#include "LCD_Driver.h"

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

static unsigned char offsetPos[8] = {
	/*THis list is used to offset positions of characters for the display */
	0,0,1,1,2,2,3,3
};

void LCD_update(unsigned char data1, unsigned char data2){
	/* LCD Blanking and Low power waveform are unchanged. */
	/* Update Display memory. */
	LCDDR0 = data1;
	LCDDR6 = data2;
}

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
	
int printAt(LCD_Driver *self, const int map) {
	union PrintPun p = {.map = map};
	int pp;
	pp = p.args.pos;
	int num = p.args.num;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
	
	return 0;
}
