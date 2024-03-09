#include "apue.h"
#include <math.h>
#include <stdio.h>
#include <sys/wait.h>

/*gcc -ansi -I../include -Wall -DLINUX -D_GNU_SOURCE  mpcalc.c -o mpcalc -L../lib -lapue -lm*/
void compare(int a, int b, int c, int d)
{
    int result1, result2;
    result1 = pow(a, b);
    result2 = pow(c, d);
    printf("------Calculating------\n");
    sleep(20);
    if (result1 > result2)
        printf("\n%d^%d is greater than %d^%d by pid=%ld\n", a, b, c, d, (long)getpid());
    else if (result1 < result2)
        printf("\n%d^%d is less than %d^%d by pid=%ld\n", a, b, c, d, (long)getpid());
    else
        printf("\n%d^%d is equal to %d^%d by pid=%ld\n", a, b, c, d, (long)getpid());
}

void prompt()
{
    int option = 1;
    pid_t pid;
    printf("\n1.Calculate\n2.Quit \nEnter your option:");
    scanf("%d", &option);
    if (option == 1)
    {
        int a, b, c, d;
        printf("Enter the values of a, b, c, and d: ");
        scanf("%d %d %d %d", &a, &b, &c, &d);
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid == 0) /*child*/
        {
            compare(a, b, c, d);
        }
        else
        {
            sleep(1);
            prompt();
        }
    }
    else if (option == 2)
        printf("\nBye!!");
    else
        printf("\nEnter a valid option!!");
}
int main(void)
{
    printf("|------------------------------------|\n");
    printf("|------Multi Process Calculator------|\n");
    printf("|------------------------------------|\n");

    prompt();

    while (wait(NULL) > 0)
        ;
    return 0;
}
