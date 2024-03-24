#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

#define MAX_CHILDREN 10

void print_status(int status)
{
    if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status) == 1)
            printf("\nFirst expression is greater.\n");
        else if (WEXITSTATUS(status) == 2)
            printf("\nSecond expression is greater.\n");
        else
            printf("\nBoth expressions are equal.\n");
    }
    else
    {
        printf("Child exited abnormally!\n");
    }
}

int main(void)
{
    printf("|------------------------------------|\n");
    printf("|------Multi Process Calculator------|\n");
    printf("|------------------------------------|\n");

    pid_t pid;
    int status[MAX_CHILDREN];
    int num_children = 0;

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
                sleep(2);
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
                if (num_children < MAX_CHILDREN)
                    status[num_children++] = 21;
                else
                    printf("Maximum number of child processes reached.\n");
            }
        }
        else if (option == 2)
        {
            int child_status;
            waitpid(pid, &child_status, 0);
            status[num_children - 1] = child_status;
            for (int i = 0; i < num_children; i++)
            {
                if (status[i] != 21)
                {
                    printf("Status for Child %d (PID %d): ", i + 1, pid);
                    print_status(status[i]);
                }
                else
                {
                    printf("No status available for Child %d (PID %d)\n", i + 1, pid);
                }
            }
        }
        else if (option == 3)
        {
            printf("\nWaiting for all children to complete...\n");
            while (wait(NULL) > 0)
                ;
            printf("\nBye!!\n");
            break;
        }
        else
        {
            printf("\nEnter a valid option!!\n");
        }
    }
    return 0;
}
