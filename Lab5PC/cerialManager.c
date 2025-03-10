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
            //printf("%s", "INPUT: ");
            for (int i = 3; i >= 0; i--) {
                int bit = (received_char >> i) & 1;
                //printf("%d", bit);
            }
            //printf("\n");
            handelInput(t, received_char);
        }
    }
    return NULL;
}

void handelInput(void *t, uint8_t data){
    /*
    Bit 0: Northbound green light status
    Bit 1: Northbound red light status
    Bit 2: Southbound green light status
    Bit 3: Southbound red light status
    */
    ThreadArgs *ts = (ThreadArgs *)t;
    u_int8_t sendData;
    switch(data){
        case 0b1010: //North = red, South = red
            changeLights((void *)&(ts->bridge), false, false);
            break;
        case 0b1001: //North = green, south = red
            sendData = 0b0010;
            //sendToAvr((void *)&(ts->serial_port), sendData);
            changeLights((void *)&(ts->bridge), true, false);
            break;
        case 0b0110: //North = red, south = green
        sendData = 0b1000;
            //sendToAvr((void *)&(ts->serial_port), sendData);
            changeLights((void *)&(ts->bridge), false, true);
            break;
        default: //This is fucked up
            //printf("PANIC SOMETING BROKE PLEASE FIX");
            break;
    }
    printStatus((void *)&(ts->bridge));
}

void sendToAvr(void *t, uint8_t command) {
    ThreadArgs *ts = (ThreadArgs *)t; // Konvertera void * till int *
    write(ts->serial_port, (const void *)&command, 1); // Använd derefererat värde
}
