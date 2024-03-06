#include "apue.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    off_t new;

    if ((fd = open("sai1.txt", O_RDWR | O_APPEND, 0777)) < 0)
        err_sys("error");
    printf("%d\n", fd);

    new = lseek(fd, 0, SEEK_SET);
    if (new == -1)
        printf("cannot seek\n");

    char *buf = "sairam";

    int err = write(fd, buf, strlen(buf));
    printf("%d\n", err);
    if (err == -1)
        err_sys("write error");

    exit(0);
}
