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
	self->isLeft = self->isLeft ? false : true;
	LCDDR13 ^= 1;
	return 0;
}

int press(GUI *self, int unUsed){
	if(self->isLeft){
		ASYNC(self->left, reset, 0);  
	} else {
		ASYNC(self->right, reset, 0); 
	}
	return 0;
}

