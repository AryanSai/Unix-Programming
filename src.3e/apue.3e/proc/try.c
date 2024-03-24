#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t child_pid;
    int status;

    child_pid = fork();

    if (child_pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        printf("Child process running with PID: %d\n", getpid());
        sleep(60);
        exit(42);
    }
    else
    {   
        printf("Parent process (PID: %d) waiting for child with PID: %d\n", getpid(), child_pid);
        if (waitpid(child_pid, &status, WNOHANG) == 0)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status))
        {
            printf("Child with PID %d exited with status: %d\n", child_pid, WEXITSTATUS(status));
        }
        else
        {
            printf("Child with PID %d exited abnormally\n", child_pid);
        }
    }

    return 0;
}
