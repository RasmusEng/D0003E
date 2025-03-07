#ifndef GUI_H
#define GUI_H

#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "PulseGenerator.h"
#include "LCD_Driver.h"

typedef struct
{
    Object super;
    int isLeft;
    PulseGenerator *left;
    PulseGenerator *right;
} GUI;

#define initGUI(left1, right2) {initObject(), false, left1, right2};
	
	
int freqUp(GUI *self, int unUsed);
int freqDown(GUI *self, int unUsed);
int switchState(GUI *self, int unUsed);
int press(GUI *self, int unUsed);
int startPulse(GUI *self, int unUsed);
#endif
