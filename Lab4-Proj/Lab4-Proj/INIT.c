#include <avr/io.h>
#include "INIT.h"


void INIT(void) {
    //LCD
    LCDCRA = (0x1 << LCDEN)   | (0x1 << LCDAB);
    LCDCRB = (0x1 << LCDCS)   | 
             (0x1 << LCDMUX1) | (0x1 << LCDMUX0) | 
             (0x1 << LCDPM2)  | (0x1 << LCDPM1)  | (0x1 << LCDPM0);
    LCDFRR = (0x1 << LCDCD2)  | (0x1 << LCDCD1)  | (0x1 << LCDCD0);
    LCDCCR = (0x1 << LCDCC3)  | (0x1 << LCDCC2)  | (0x1 << LCDCC1)  | (0x1 << LCDCC0);

    //Joystick.
    PORTB  = (0x1 << PB7)     | (0x1 << PB6)     | (0x1 << PB4);
    PORTE  = (0x1 << PE3)     | (0x1 << PE2);
    EIMSK  = (0x1 << PCIE1)   | (0x1 << PCIE0);
    PCMSK0 = (0x1 << PCINT3)  | (0x1 << PCINT2);
    PCMSK1 = (0x1 << PCINT15) | (0x1 << PCINT14) | (0x1 << PCINT12);
}