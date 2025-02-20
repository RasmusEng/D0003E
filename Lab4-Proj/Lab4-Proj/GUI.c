#include "GUI.h"

//FIX RAPID INCREASE (HOLDING UP/DOWN SHOULD GO FAST AS FUCK )
//Fix sync and async calls
//MAKE SURE TO INIT PINE and PINB!!!!!!
//Might need to be switched PE2 and PE3
void joyStickVerticalControll(){
    if (!(PINE & (1 << PE2))) { //LEFT
        moveLeft();
    }
    if (!(PINE & (1 << PE3))) { //RIGHT
        moveRight();
    }
}

void joyStickHorizontalControll(){
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
    if(left){
        self->left->increase();
    }else{
        self->right->increase();
    }
}   

void freqDown(GUI *self){
    if(left){
        self->left->decrease();
    }else{
        self->right->decrease();
    }
}

void moveLeft(GUI *self){
    self->left = true;
}

void  moveRight(GUI *self){
    self->left = false;
}

void press(GUI *self){
    if(left){
        self->left->reset();
    }else{
        self->right->reset();
    }
}
