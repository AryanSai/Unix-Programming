#include "apue.h"
#include <fcntl.h>

int main(void)
{
    int fd;

    if ((fd = creat("file1.txt", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH)) < 0)
        err_sys("creat error");

    if ((fd = creat("file2.txt", S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
        err_sys("creat error");

    if ((fd = creat("file3.txt", 0777)) < 0)
        err_sys("creat error");

    exit(0);
}