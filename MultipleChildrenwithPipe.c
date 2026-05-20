#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pid_t writer, reader;

    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        exit(1);
    }

    /* ---------------- First Child: Writer ---------------- */
    writer = fork();

    if (writer < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (writer == 0)
    {
        close(fd[0]); // close read end

        int numbers[] = {1, 2, 3, 4, 5};

        write(fd[1], numbers, sizeof(numbers));

        close(fd[1]);

        printf("Child 1 (Writer): Numbers sent to pipe\n");

        exit(0);
    }

    /* ---------------- Second Child: Reader ---------------- */
    reader = fork();

    if (reader < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (reader == 0)
    {
        close(fd[1]); // close write end

        int arr[5];
        int sum = 0;

        read(fd[0], arr, sizeof(arr));

        for (int i = 0; i < 5; i++)
        {
            sum += arr[i];
        }

        close(fd[0]);

        printf("Child 2 (Reader): Sum = %d\n", sum);

        exit(0);
    }

    /* ---------------- Parent Process ---------------- */

    close(fd[0]);
    close(fd[1]);

    // Wait for both children
    wait(NULL);
    wait(NULL);

    printf("Parent: Both children finished execution\n");

    return 0;
}