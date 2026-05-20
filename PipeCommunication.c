#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int p2c[2]; // Parent → Child
    int c2p[2]; // Child → Parent

    pid_t pid;
    int number = 7;
    int result;

    // Create pipes
    if (pipe(p2c) == -1 || pipe(c2p) == -1)
    {
        perror("Pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }

    /* ---------------- CHILD PROCESS ---------------- */
    if (pid == 0)
    {
        close(p2c[1]); // close write end (parent → child)
        close(c2p[0]); // close read end (child → parent)

        // Read number from parent
        read(p2c[0], &number, sizeof(number));

        printf("Child received: %d\n", number);

        // Compute square
        result = number * number;

        // Send result back to parent
        write(c2p[1], &result, sizeof(result));

        close(p2c[0]);
        close(c2p[1]);

        exit(0);
    }

    /* ---------------- PARENT PROCESS ---------------- */
    else
    {
        close(p2c[0]); // close read end (parent → child)
        close(c2p[1]); // close write end (child → parent)

        // Send number to child
        write(p2c[1], &number, sizeof(number));

        // Receive result from child
        read(c2p[0], &result, sizeof(result));

        printf("Parent received squared result: %d\n", result);

        close(p2c[1]);
        close(c2p[0]);
    }

    return 0;
}