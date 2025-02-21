#include "GUI.h"
#include "LCD_Driver.h"
#include "PulseGenerator.h"
#include <avr/io.h>
//TODO: Check every call if it should be SYNC or ASYNC

void freqUp(GUI *self){
	if(self->isLeft){
		SYNC(&(self->left), increase, 0);
	}else{
		SYNC(&(self->right), increase, 0);
	}
}

void freqDown(GUI *self){
	if(self->isLeft){
		SYNC(&(self->left), decrease, 0);
	}else{
		SYNC(&(self->right), decrease, 0);
	}
}

void moveLeft(GUI *self){
    self->isLeft = true;
	SYNC(self, switchIndicator,0);
}

void  moveRight(GUI *self){
    self->isLeft = false;
    SYNC(self, switchIndicator,0);
}

void press(GUI *self){
    if(self->isLeft){
        SYNC(self->left, reset,0);
    }else{
		SYNC(self->right, reset,0);
    }
}

//FIX RAPID INCREASE (HOLDING UP/DOWN SHOULD GO FAST AS FUCK )
//Might need to be switched PE2 and PE3
void joyStickVerticalControll(GUI *self){
    if (!(PINE & (1 << PE2))) { //LEFT
        SYNC(self, moveLeft, 0);
    }
    if (!(PINE & (1 << PE3))) { //RIGHT
        SYNC(self, moveRight, 0);
    }
}

void joyStickHorizontalControll(GUI *self){
    if (!(PINB & (1 << PB7))) { //DOWN
		SYNC(self, freqDown, 0);
    }
    if (!(PINB & (1 << PB6))) { //UP
		SYNC(self, freqUp, 0);
    }
    if (!(PINB & (1 << PB4))) { //PRESS
        SYNC(self, press, 0);
    }
}
