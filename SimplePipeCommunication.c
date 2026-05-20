#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];  // fd[0] = read end, fd[1] = write end
    pid_t pid;
    char buffer[100];
    char message[] = "Hello from Parent Process via Pipe!";

    // Create pipe
    if (pipe(fd) == -1)
    {
        perror("Pipe failed");
        return 1;
    }

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    // Parent process
    if (pid > 0)
    {
        close(fd[0]); // Close unused read end

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]); // Close write end after sending

        printf("Parent: Message sent to child.\n");
    }

    // Child process
    else
    {
        close(fd[1]); // Close unused write end

        read(fd[0], buffer, sizeof(buffer));

        printf("Child received message: %s\n", buffer);

        close(fd[0]);
    }

    return 0;
}