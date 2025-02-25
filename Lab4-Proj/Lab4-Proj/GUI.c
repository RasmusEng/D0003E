#include "GUI.h"
#include "LCD_Driver.h"
#include "PulseGenerator.h"
#include <avr/io.h>
//TODO: Check every call if it should be SYNC or SYNC

int freqUp(GUI *self, int unUsed){
	if(self->isLeft){
		ASYNC(self->left, increase, 0);	
	}else{
		ASYNC(self->right, increase, 0);
		//Call generator her or in increase?
	}
	
	return 0;
}

int freqDown(GUI *self, int unUsed){
	if(self->isLeft){
		ASYNC(self->left, decrease, 0);
	}else{
		ASYNC(self->right, decrease, 0);
	}
	return 0;
}

int switchState(GUI *self, int unUsed){
    self->isLeft ^= true;
	ASYNC(self, switchIndicator, 0);
	return 0;
}

int press(GUI *self, int unUsed){
    if(self->isLeft){
        ASYNC(self->left, reset,0);
    }else{
		ASYNC(self->right, reset,0);
    }
	return 0;
}

int joyStickHorizontalControll(GUI *self, int unUsed){
	AFTER(MSEC(200), self, switchState, 0);
	//ASYNC(self,switchState, 0);
	return 0;
}

int joyStickVerticalControll(GUI *self, int unUsed){
    if (!(PINB & (1 << PB7))) { //DOWN
		//SYNC(self, freqDown, 0);
		AFTER(MSEC(200), self, freqDown, 0);
    }
    if (!(PINB & (1 << PB6))) { //UP
		//SYNC(self, freqUp, 0);
		//AFTER(MSEC(holdDelay), self, freqUp, 0);
		ASYNC(self, freqUp, 0);
		
    }
    if (!(PINB & (1 << PB4))) { //PRESS
        //SYNC(self, press, 0);s
		AFTER(MSEC(200), self, press, 0);
    }
	// Todo fixa rätt return
	return 0;
}
