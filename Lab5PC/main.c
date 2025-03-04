#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include <unistd.h>

#define MAX_CARS 100000000 // Max antal bilar i kön

dispatch_semaphore_t bridge;  // GCD-semafor för bron

void* car_simulation(void* arg) {
    char direction = *(char*)arg;
    free(arg);

    printf("Bil från %c väntar på att korsa bron...\n", direction);
    dispatch_semaphore_wait(bridge, DISPATCH_TIME_FOREVER);

    printf("Bil från %c har korsat bron.\n", direction);
    dispatch_semaphore_signal(bridge);

    return NULL;
}

int main() {
    pthread_t cars[MAX_CARS];
    int car_count = 0;
    char input;

    bridge = dispatch_semaphore_create(1);  // Initiera semafor (1 bil åt gången)

    printf("Kommando:\n");
    printf("  's' - Ny bil söderut\n");
    printf("  'n' - Ny bil norrut\n");
    printf("  'e' - Avsluta simulatorn\n");

    while (1) {
        printf("\e[1;1H\e[2J");
        input = getchar();
        while (getchar() != '\n');  // Rensa bufferten

        if (input == 'e') {
            printf("Avslutar simulatorn...\n");
            break;
        } else if (input == 's' || input == 'n') {
            if (car_count >= MAX_CARS) {
                printf("Max antal bilar nått!\n");
                continue;
            }

            char* direction = malloc(sizeof(char));
            *direction = input;
            pthread_create(&cars[car_count], NULL, car_simulation, direction);
            car_count++;
        } else {
            printf("Felaktigt kommando! Använd 's', 'n' eller 'e'.\n");
        }
    }

    for (int i = 0; i < car_count; i++) {
        pthread_join(cars[i], NULL);
    }

    return 0;
}
