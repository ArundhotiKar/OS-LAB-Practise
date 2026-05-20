#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

static void errExit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

static int idata = 111; /* Allocated in data segment */

int main(int argc, char *argv[])
{
    int istack = 222; /* Allocated in stack segment */

    pid_t childPid;

    switch (childPid = fork())
    {
        case -1:
            errExit("fork");

        case 0: /* Child process */
            idata *= 3;
            istack *= 3;
            break;

        default: /* Parent process */
            sleep(3); /* Give child a chance to execute */
            break;
    }

    /* Both parent and child come here */

    printf("PID=%ld %s idata=%d istack=%d\n",
           (long)getpid(),
           (childPid == 0) ? "(child)" : "(parent)",
           idata,
           istack);

    exit(EXIT_SUCCESS);
}