#include "Bridge.h"
#include <pthread.h>

pthread_mutex_t block;


void addCarQueue(Bridge *b, int Side){
    pthread_mutex_lock(&block);
    if(Side){
        b->northQueueSize++;
    }else{
        b->southQueueSize++;
    }
    pthread_mutex_unlock(&block);
}


void changeLights(Bridge *b, bool north, bool south){
    pthread_mutex_lock(&block);
    b->northGreen = north;
    b->southGreen = south;
    pthread_mutex_unlock(&block);
}
