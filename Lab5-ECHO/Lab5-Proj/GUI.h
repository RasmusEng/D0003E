#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"
#include <stdbool.h>
#include "PulseGenerator.h"

typedef struct
{
    Object super;
} GUI;

#define initGUI() {initObject()};
	
#endif
