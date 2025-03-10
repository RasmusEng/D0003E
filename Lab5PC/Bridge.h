#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
#endif