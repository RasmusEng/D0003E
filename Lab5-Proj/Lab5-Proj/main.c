#include "InteruptHandler.h"
#include "USARTSender.h"
#include "TinyTimber.h"
#include "LCD_Driver.h"
#include "Bridge.h"
#include "Init.h"

int main(void)
{
	init();
	LCD_Driver lcd = initLCD_Driver();
	USARTSender usart = initUSARTSender();
	Bridge bridge = initBridge(&usart, &lcd);
	InterruptHandler inter = initInterruptHandler(&bridge);
	
	INSTALL(&inter, input, IRQ_USART0_RX);
	
	return TINYTIMBER(NULL, NULL, NULL);
}