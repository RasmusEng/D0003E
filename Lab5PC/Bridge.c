#include "Bridge.h"
#include <pthread.h>

pthread_mutex_t block;

pthread carRemover;

void *idleFunction(void *t){
    Bridge* b = (Bridge *)b;
    sleep(5);
    removeCarBridge(b);
    pthread_exit(NULL);
}

void addCarQueue(Bridge *b, int Side){
    pthread_mutex_lock(&block);
    if(Side){
        b->northQueueSize++;
    }else{
        b->southQueueSize++;
    }
    printStatus(b);
    pthread_mutex_unlock(&block);
}

void removeCarBridge(Bridge *b){
    pthread_mutex_lock(&block);
    b->carsOnBridge--;
    printStatus(b);
    pthread_mutex_unlock(&block);
}


void changeLights(Bridge *b, bool north, bool south){
    pthread_mutex_lock(&block);
    b->northGreen = north;
    b->southGreen = south;
    printStatus(b);
    pthread_mutex_unlock(&block);
}

void handelInput(void *t, uint8_t data){
    ThreadArgs *ts = (ThreadArgs *)t;
    u_int8_t sendData;
    switch(data){
        case 0b1010: //North = red, South = red
            changeLights((void *)&(ts->bridge), false, false);
            break;
        case 0b1001: //North = green, south = red
            sendData = 0b0010;  
            changeLights((void *)&(ts->bridge), true, false);
            if((void *)&(ts->bridge->northQueueSize)){
                pthread_mutex_lock(&block);
                (void *)&(ts->bridge->northQueueSize--);
                sendToAvr((void *)&(ts->serial_port), sendData);
                printStatus((void *)&(ts->bridge));
                pthread_mutex_unlock(&block);
                pthread_create(&carRemover, NULL, idleFunction, b);
            }
            break;
        case 0b0110: //North = red, south = green
            sendData = 0b1000;
            changeLights((void *)&(ts->bridge), false, true);
            if((void *)&(ts->bridge->southQueueSize)){
                pthread_mutex_lock(&block);
                (void *)&(ts->bridge->southQueueSize--);
                sendToAvr((void *)&(ts->serial_port), sendData);
                printStatus((void *)&(ts->bridge));
                pthread_mutex_unlock(&block);
                pthread_create(&carRemover, NULL, idleFunction, b);c
            }
            break;
        default: //This is fucked up
            break;
    }
    printStatus((void *)&(ts->bridge));
}