#ifndef THREADSTRUCT_H_
#define THREADSTRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include "Bridge.h"

typedef struct {
    int serial_port;
    Bridge *bridge;
} ThreadArgs;

#define initThreadArgs(serialPort, bridge) {serialPort, bridge};

#endif