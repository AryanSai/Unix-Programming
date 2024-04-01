/* - Write a shell program. It should have the following features:
1. You should be able to execute any commands (programs) with arguments (Figure 1.7 of APUE does not
allow any arguments for a command).
2. The termination status and exit status (if any) of the executed program should be reported after
termination of the program.
3. Optional: You should allow the user to execute programs in the background.
4. Optional: You should allow user to create / modify environment variables and export them. You should
 test whether a newly created shell variable which is exported is getting specified in the environment
 variables of the programs executed from the shell.
5. Any additional features from your side are very welcome
*/

#include "apue.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define HISTORY_SIZE 100

char history[HISTORY_SIZE][MAXLINE];
int history_count = 0;

void add_to_history(const char *command)
{
    if (history_count < HISTORY_SIZE)
    {
        strcpy(history[history_count], command);
        history_count++;
    }
    else
    {
        printf("History is full!\n");
    }
}

void display_history()
{
    printf("Command History:\n");
    int i = 0;
    while (i < history_count)
    {
        printf("%d  %s\n", i + 1, history[i]);
        i++;
    }
}

void control_c(int signum)
{
    printf("\nCtrl+C pressed. Bye!\n");
    exit(0);
}

int main(void)
{
    char buf[MAXLINE];
    int status;

    signal(SIGINT, control_c); /*signal to handle ctrl + c */

    printf("------------Welcome to the SeaShell------------\n");
    printf("$ "); /* print dollar prompt */
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0; /* replace newline with null */

        add_to_history(buf);

        /* extract the command */
        char *command = strtok(buf, " ");

        /* when the command is cd */
        if (strcmp(command, "cd") == 0)
        {
            char *arg = strtok(NULL, " ");
            if (arg == NULL)
            {
                fprintf(stderr, "cd: missing argument\n");
            }
            else
            {
                if (chdir(arg) != 0) /*if cd fails*/
                {
                    perror("cd");
                }
                else
                {
                    char cwd[MAXLINE];                    /*to hold pwd*/
                    if (getcwd(cwd, sizeof(cwd)) == NULL) /*get the pwd*/
                    {
                        perror("getcwd");
                    }
                    else
                    {                                   /*set the environment variable PWD to the new one*/
                        if (setenv("PWD", cwd, 1) != 0) /* 1 => rewrite*/
                        {
                            perror("setenv");
                        }
                    }
                }
            }
        }
        else if (strcmp(command, "history") == 0) /*when the command is history*/
        {
            display_history();
        }
        else
        {
            if ((status = system(buf)) < 0)
                err_sys("system() error");
        }
        printf("$ ");
    }
    exit(0);
}
