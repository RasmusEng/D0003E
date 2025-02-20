#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"
#include <stdbool.h>

typedeff struct
{
    Object super;
    bool left;
    PulseGenerator left;
    PulseGenerator right;
} GUI;

#define initGUI(left, right) {initObject(), false, left, right};


#endif