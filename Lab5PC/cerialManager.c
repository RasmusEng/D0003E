#include "cerialManager.h"
#include "Bridge.h"
#include "Display.h"
#include "threadStruct.h"

void *readAVR(void *t){
    uint8_t received_char;
    ThreadArgs *ts = (ThreadArgs *)t;
    while (1) {
        int bytes_read = read(ts->serial_port, &received_char, 1); // Läs en byte
        if (bytes_read > 0 && received_char != 0) {
            handelInput(t, received_char);
        }
    }
    return NULL;
}

void sendToAvr(void *t, uint8_t command) {
    ThreadArgs *ts = (ThreadArgs *)t; // Konvertera void * till int *
    write(ts->serial_port, (const void *)&command, 1); // Använd derefererat värde
}
