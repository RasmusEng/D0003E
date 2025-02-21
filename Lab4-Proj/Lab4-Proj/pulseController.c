#include "PulseController.h"
#include <avr/io.h>

void sendSignal(PulseController *self, int pin){
    if(pin == 1){
        PORTE ^= (1 << PE4);
    }else if(pin == 3){
        PORTE ^= (1 << PE6);
    }
}