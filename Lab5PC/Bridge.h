#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "threadStruct.h"

typedef struct{
    bool northGreen;
    bool southGreen;
    int northQueueSize;
    int southQueueSize;
    int carsOnBridge;
} Bridge;

#define initBridge() {false, false, 0,0,0}

void addCarQueue(Bridge *b, int Side);
void changeLights(Bridge *b, bool north, bool south);
void handelInput(void *t, uint8_t data);
void removeCarBridge(Bridge *b);
void *idleFunction(void *t);

#endif