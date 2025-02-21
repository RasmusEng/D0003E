#include "PulseController.h"

//Make sure to handel race conditions in this thingi ಥ_ಥ
void sendSignal(int pin){
    if(pin == 1){
        PORTE ^= (1 << PE4);
    }else if(pin == 3){
        PORTE ^= (1 << PE6);
    }
}