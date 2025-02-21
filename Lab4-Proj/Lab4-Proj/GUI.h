#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"
#include <stdbool.h>

typedef struct
{
    Object super;
    bool isLeft;
    PulseGenerator *left;
    PulseGenerator *right;
} GUI;

#define initGUI(left1, right2) {initObject(), false, left1, right2};
	
void joyStickHorizontalControll();
void joyStickVerticalControll();

#endif