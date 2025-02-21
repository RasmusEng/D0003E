#include "GUI.h"
#include "LCD_Driver.h"
#include <avr/io.h>

//FIX RAPID INCREASE (HOLDING UP/DOWN SHOULD GO FAST AS FUCK )
//Fix sync and async calls
//MAKE SURE TO INIT PINE and PINB!!!!!!
//Might need to be switched PE2 and PE3
void joyStickVerticalControll(GUI *self){
    if (!(PINE & (1 << PE2))) { //LEFT
        moveLeft(self);
    }
    if (!(PINE & (1 << PE3))) { //RIGHT
        moveRight(self);
    }
}

void joyStickHorizontalControll(GUI *self){
    if (!(PINB & (1 << PB7))) { //DOWN
        freqDown();
    }
    if (!(PINB & (1 << PB6))) { //UP
        freqUp();
    }
    if (!(PINB & (1 << PB4))) { //PRESS
        press();
    }
}

void freqUp(GUI *self){
	if(self->isLeft){
		increase(&(self->left));
		}else{
		increase(&(self->right));
	}
}

void freqDown(GUI *self){
	if(self->isLeft){
		decrease(&(self->right));
		}else{
		decrease(&(self->right));
	}
}

void moveLeft(GUI *self){
    self->left = true;
    switchIndicator(); //Sync or Async?
}

void  moveRight(GUI *self){
    self->left = false;
    switchIndicator(); //Sync or Async?
}

void press(GUI *self){
    if(self->isLeft){
        reset(self->left);
    }else{
		reset(self->right);
    }
}
