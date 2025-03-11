#include "Display.h"
#include <stdio.h>
#include "Bridge.h"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void printStatus(Bridge *b)
{       
        printf(WHT "%d" RESET, b->southQueueSize);
        printf(CYN "%s" RESET, "  ");
        if (b->southGreen)
        {
        printf(GRN "%s" RESET, "O");
        }
        else
        {
                printf(RED "%s" RESET, "X");
        }
        printf(CYN "%s" RESET, "  ");
        printf(MAG "%d" RESET, b->carsOnBridge);
        printf(CYN "%s" RESET, "  ");
        if (b->northGreen)
        {
                printf(GRN "%s" RESET, "O");
        }
        else
        {
                printf(RED "%s" RESET, "X");
        }
        printf(CYN "%s" RESET, "  ");
        printf(WHT "%d\n" RESET, b->northQueueSize);
}