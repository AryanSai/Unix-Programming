#include "apue.h"
#include <fcntl.h>
int main(void)
{
    if (creat("tempfile.txt", 0777) < 0)
        err_sys("open error");

    printf("file created\n");

    /*Check for the created file using ls*/
    sleep(10);

    if (unlink("tempfile.txt") < 0)
        err_sys("unlink error");

    printf("file deleted!\n");

    exit(0);
}