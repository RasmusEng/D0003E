#ifndef INIT_H
#define INIT_H

#include <stdbool.h>
#include <avr/io.h>
#include "PulseGenerator.h"
#include "LCD_Driver.h"
#define SET(x) (1 << x)

void INIT();
#endif