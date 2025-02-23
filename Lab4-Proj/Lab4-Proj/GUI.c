#include "GUI.h"
#include "LCD_Driver.h"
#include "PulseGenerator.h"
#include <avr/io.h>
//TODO: Check every call if it should be SYNC or SYNC

int freqUp(GUI *self, int unUsed){
	if(self->isLeft){
		SYNC(self->left, increase, 0);
	}else{
		SYNC(self->right, increase, 0);
	}
	return 0;
}

int freqDown(GUI *self, int unUsed){
	if(self->isLeft){
		SYNC(self->left, decrease, 0);
	}else{
		SYNC(self->right, decrease, 0);
	}
	return 0;
}

int switchState(GUI *self, int unUsed){
    self->isLeft ^= true;
	LCDDR13 ^= 1;
	return 0;
}

int press(GUI *self, int unUsed){
    if(self->isLeft){
        SYNC(self->left, reset,0);
    }else{
		SYNC(self->right, reset,0);
    }
	return 0;
}

//FIX RAPID INCREASE (HOLDING UP/DOWN SHOULD GO FAST AS FUCK )
//Might need to be switched PE2 and PE3
int joyStickHorizontalControll(GUI *self, int unUsed){
	SYNC(self,switchState, 0);
}

int joyStickVerticalControll(GUI *self, int unUsed){
    if (!(PINB & (1 << PB7))) { //DOWN
		SYNC(self, freqDown, 0);
    }
    if (!(PINB & (1 << PB6))) { //UP
		SYNC(self, freqUp, 0);
    }
    if (!(PINB & (1 << PB4))) { //PRESS
        SYNC(self, press, 0);
    }
	// Todo fixa rätt return
	return 0;
}
