#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

void print_status(int status)
{
    if (WEXITSTATUS(status) == 1)
        printf("\nFirst expression is greater.\n");
    else if (WEXITSTATUS(status) == 2)
        printf("\nSecond expression is greater.\n");
    else
        printf("\nBoth expressions are equal.\n");
}
int main(void)
{
    printf("|------------------------------------|\n");
    printf("|------Multi Process Calculator------|\n");
    printf("|------------------------------------|\n");

    pid_t pid;
    int status = 0;

    while (1)
    {
        int option;
        printf("\n1. Calculate\n2. Check Previous Result\n3. Quit\nEnter your option: ");

        if (scanf("%d", &option) != 1)
        {
            printf("\nInvalid input. Please enter a valid option.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (option == 1)
        {
            int a, b, c, d;
            printf("Enter the values of a, b, c, and d: ");
            if (scanf("%d %d %d %d", &a, &b, &c, &d) != 4)
            {
                printf("\nInvalid input. Please enter four integers separated by spaces.\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            pid = fork();
            if (pid < 0)
            {
                perror("fork error");
            }
            else if (pid == 0)
            {
                int result1, result2;
                result1 = pow(a, b);
                result2 = pow(c, d);
                sleep(60);
                if (result1 > result2)
                    exit(1);
                else if (result1 < result2)
                    exit(2);
                else
                    exit(0);
            }
            else
            {
                printf("Parent process PID: %d\n", getpid());
                printf("Child Process %d is calculating...\n", pid);
            }
        }
        else if (option == 2)
        {
            if (waitpid(-1, &status, WNOHANG) == 0)
            {
                printf("\nNo calculation has been performed yet.\n");
                continue;
            }
            if (WIFEXITED(status))
            {
                print_status(status);
            }
            else
                printf("Child with PID %d exited abnormally!\n", pid);
        }
        else if (option == 3)
        {
            printf("\nWaiting for all children to complete...\n");
            while (waitpid(-1, &status, 0) > 0)
            {
                print_status(status);
            }
            printf("\nBye!!\n");
            break;
        }
        else
            printf("\nEnter a valid option!!\n");
    }
    return 0;
}