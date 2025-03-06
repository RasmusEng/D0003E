#include "GUI.h"

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
	self->isLeft = !self->isLeft;
	LCDDR13 ^= 1; //Indicator
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

int startPulse(GUI *self, int unUsed){
	ASYNC(self->left, generator, 0);
	ASYNC(self->right, generator, 0);
	
	return unUsed;
}
