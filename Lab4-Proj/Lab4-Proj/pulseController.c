#include "PulseController.h"

//Make sure to handel race conditions in this thingi ಥ_ಥ
void sendSignal(int pin){
    if(pin == 1){
        PORTE ^= (0x1 << PE1);
    }else if(pin == 3){
        PORTE ^= (0x1 << PE3);
    }
}