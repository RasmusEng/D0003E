#include "LCD_Driver.h"
void INIT(){
    CLKPR = 0x80;
	CLKPR = 0x00;

    LCD_Init();
    
}