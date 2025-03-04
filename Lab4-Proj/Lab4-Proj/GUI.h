#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"
#include <stdbool.h>
#include "PulseGenerator.h"

typedef struct
{
    Object super;
    bool isLeft;
    PulseGenerator *left;
    PulseGenerator *right;
} GUI;

#define initGUI(left1, right2) {initObject(), false, left1, right2};
	
	
int freqUp(GUI *self, int unUsed);
int freqDown(GUI *self, int unUsed);
int switchState(GUI *self, int unUsed);
int press(GUI *self, int unUsed);
void startPulse(GUI *self, int unUsed);
#endif
