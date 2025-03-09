#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"

typedef struct
{
	Object super;
	int NorthScreenPos;
	int SouthScreenPos;
	int CarsOnBridgePos;
}GUI;

#define initGUI() {initObject(), 4, 0, 2}

#endif /* GUI_H_ */