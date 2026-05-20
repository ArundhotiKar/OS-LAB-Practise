#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char globBuf[65536];          /* Uninitialized data segment (BSS) */
int primes[] = {2, 3, 5, 7}; /* Initialized data segment */

/* Function stored in Text segment */
static int square(int x)
{
    int result; /* Stored in stack frame of square() */
    result = x * x;
    return result;
}

/* Function stored in Text segment */
static void doCalc(int val)
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000)
    {
        int t; /* Stored in stack frame of doCalc() */
        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int main(int argc, char *argv[])
{
    static int key = 9973;       /* Initialized data segment */
    static char mbuf[10240000];  /* Uninitialized data segment (BSS) */

    char *p; /* Local variable stored on stack */

    /* Allocate memory from heap */
    p = malloc(1024);

    if (p == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    printf("\nMemory addresses of variables and segments:\n");
    printf("---------------------------------------------------\n");

    /* Text segment */
    printf("Address of function main() (Text): %p\n", (void *)main);
    printf("Address of function doCalc() (Text): %p\n", (void *)doCalc);

    /* Data segment */
    printf("Address of primes (Initialized Data): %p\n", (void *)primes);
    printf("Address of key (Initialized Data): %p\n", (void *)&key);

    /* BSS segment */
    printf("Address of globBuf (BSS): %p\n", (void *)globBuf);
    printf("Address of mbuf (BSS): %p\n", (void *)mbuf);

    /* Heap segment */
    printf("Address of malloc'd memory (Heap): %p\n", (void *)p);

    /* Stack segment */
    printf("Address of local variable p (Stack): %p\n", (void *)&p);

    printf("\nProcess ID: %d\n", getpid());
    printf("To see segment boundaries, run:\n");
    printf("cat /proc/%d/maps\n", getpid());

    printf("\n---------------------------------------------\n");

    doCalc(key);

    printf("\nPress Enter to continue...\n");
    getchar(); /* Pause program so user can inspect /proc/PID/maps */

    free(p);

    return EXIT_SUCCESS;
}