#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pid_t pid1, pid2;

    // Create pipe
    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        exit(1);
    }

    // First child → executes ls
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0)
    {
        // Redirect stdout to pipe write end
        dup2(fd[1], STDOUT_FILENO);

        // Close unused ends
        close(fd[0]);
        close(fd[1]);

        // Execute ls
        execlp("ls", "ls", NULL);

        perror("execlp ls failed");
        exit(1);
    }

    // Second child → executes grep ".c"
    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid2 == 0)
    {
        // Redirect stdin to pipe read end
        dup2(fd[0], STDIN_FILENO);

        // Close unused ends
        close(fd[1]);
        close(fd[0]);

        // Execute grep ".c"
        execlp("grep", "grep", ".c", NULL);

        perror("execlp grep failed");
        exit(1);
    }

    // Parent process closes both ends
    close(fd[0]);
    close(fd[1]);

    // Wait a bit for children to finish
    sleep(2);

    return 0;
}