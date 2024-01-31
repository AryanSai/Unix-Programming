/* Write a simple touch program called mytouch which takes a filename as argument. The program should update the access and modification time to the current time.*/

#include "apue.h"
#include <fcntl.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int fd;
    struct stat statbuf;
    struct timespec new_times[2];
    struct timespec current_time;

    /*open the file*/
    if ((fd = open(argv[1], O_RDWR)) < 0)
        err_ret("%s: open error", argv[1]);

    /*get the stat of the file*/
    if (stat(argv[1], &statbuf) < 0)
        err_ret("%s: stat error", argv[1]);

    /*get current time*/
    if (clock_gettime(CLOCK_REALTIME, &current_time) == -1)
    {
        perror("clock_gettime");
        return 1;
    }
    /*copy the current time to the timespec struct*/
    new_times[0] = current_time;
    new_times[1] = current_time;

    /*change the access and modification times*/
    if (futimens(fd, new_times) < 0)
        err_ret("%s: futimens error", argv[1]);

    close(fd);
    exit(0);
}
