#include <stdio.h>
#include <stdlib.h>

/* Global variable */
int globalVar = 100;

/* Function to determine memory segment */
void identifySegment(void *ptr, void *stackVar, void *heapVar)
{
    if (ptr == heapVar)
    {
        printf("Variable belongs to HEAP segment\n");
    }
    else if (ptr == stackVar)
    {
        printf("Variable belongs to STACK segment\n");
    }
    else if (ptr == &globalVar)
    {
        printf("Variable belongs to GLOBAL/DATA segment\n");
    }
    else
    {
        printf("Unknown memory segment\n");
    }
}

int main()
{
    int stackVar = 10;               /* Stack variable */
    int *heapVar = malloc(sizeof(int)); /* Heap variable */

    if (heapVar == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    *heapVar = 20;

    printf("Address of globalVar : %p\n", (void *)&globalVar);
    printf("Address of stackVar  : %p\n", (void *)&stackVar);
    printf("Address of heapVar   : %p\n\n", (void *)heapVar);

    /* Test variables */
    identifySegment(&globalVar, &stackVar, heapVar);
    identifySegment(&stackVar, &stackVar, heapVar);
    identifySegment(heapVar, &stackVar, heapVar);

    free(heapVar);

    return 0;
}