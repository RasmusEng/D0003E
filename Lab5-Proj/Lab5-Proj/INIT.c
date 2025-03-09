#include <avr/io.h>
#include "INIT.h"

#define FOSC 8000000
#define BAUD 9600
#define MYUBRR (FOSC / (16UL * BAUD) - 1)

void init(){
	//LCD
	LCDCRA = (0x1 << LCDEN)   | (0x1 << LCDAB);
	LCDCRB = (0x1 << LCDCS)   |
	(0x1 << LCDMUX1) | (0x1 << LCDMUX0) |
	(0x1 << LCDPM2)  | (0x1 << LCDPM1)  | (0x1 << LCDPM0);
	LCDFRR = (0x1 << LCDCD2)  | (0x1 << LCDCD1)  | (0x1 << LCDCD0);
	LCDCCR = (0x1 << LCDCC3)  | (0x1 << LCDCC2)  | (0x1 << LCDCC1)  | (0x1 << LCDCC0);
	
	//USART
	UBRR0H = (uint8_t)(MYUBRR<<8);
	UBRR0L = (uint8_t)(MYUBRR);

	
	UCSR0B = (1<<RXEN0)  | (1<<TXEN0)  | (1<<RXCIE0);

	UCSR0C = (0<<UCSZ01) | (3<<UCSZ00);
}