#include "InteruptHandler.h"
#include "USARTSender.h"
#include "TinyTimber.h"
#include "LCD_Driver.h"
#include "Bridge.h"
#include "Init.h"
#include "GUI.h"

int main(void)
{
	init();
	GUI gui = initGUI();
	LCD_Driver lcd = initLCD_Driver();
	USARTSender usart = initUSARTSender();
	Bridge bridge = initBridge(&gui, &usart, &lcd);
	InterruptHandler inter = initInterruptHandler(&bridge);
	
	INSTALL(&inter, input, IRQ_USART0_RX);
	
	return TINYTIMBER(&lcd, startSequence, 1);
}