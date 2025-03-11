#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include "init.h"
#include "Display.h"
#include "cerialManager.h"
#include "Bridge.h"
#include "threadStruct.h"

void menu(){
    printf("Kommando:\n");
    printf("  's' - Ny bil söderut\n");
    printf("  'n' - Ny bil norrut\n");
    printf("  'e' - Avsluta simulatorn\n");
}

void commands(int serial_port, Bridge *b){
    uint8_t SOUTH = 0b0100;
    uint8_t NORTH = 0b0001; 
    char input;
    while(1){
        input = getchar();
        while (getchar() != '\n');
        if (input == 'e'){
            printf("---Avslutar Bridge Simulator Controll Center---");
            break;
        }
        else if (input == 'n'){
            addCarQueue(b, 1);
            write(serial_port, &NORTH, 1);
            continue;
        }
        else if (input == 's'){
            addCarQueue(b, 0);
            write(serial_port, &SOUTH, 1);
            continue;
        }
    }
}

int main() {
    printf("---Bridge Simulator Controll Center---\n");
    menu();
    printf("--------------------------------------\n");

    Bridge bridge = initBridge();
    int serial_port = init();
    ThreadArgs thread = initThreadArgs(serial_port, &bridge);

    printStatus(&bridge);

    pthread_t threadID;
    pthread_create(&threadID, NULL, readAVR, &thread);
    
    commands(serial_port, &bridge);
    
    close(serial_port);
    return 0;
}
