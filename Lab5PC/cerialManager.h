#ifndef CERIALMANAGER_H_
#define CERIALMANAGER_H_
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include "threadStruct.h"


void *readAVR(void *Threads);
void handelInput(void *Threads, uint8_t data);
void sendToAvr(void *Threads, uint8_t command);
#endif