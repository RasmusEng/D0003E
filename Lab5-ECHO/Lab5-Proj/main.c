#include <avr/io.h>
#define FOSC 8000000
#define BAUD 9600
#define MYUBRR (FOSC / (16UL * BAUD) - 1)

void INIT(void) {
	
	UBRR0H = (uint8_t)(MYUBRR<<8);
	UBRR0L = (uint8_t)(MYUBRR);

	
	UCSR0B = (1<<RXEN0)  | (1<<TXEN0)  | (1<<RXCIE0);

	UCSR0C = (0<<UCSZ01) | (3<<UCSZ00);
}

uint8_t USART_Receive( void )
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_Transmit(uint8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}



int main(void)
{
	INIT();
	while (1)
	{
		uint8_t temp = USART_Receive();
		USART_Transmit(temp);
	}
}

