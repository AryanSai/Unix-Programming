#include "apue.h"
#include <fcntl.h>
int main(void)
{
    if (creat("tempfile.txt", 0777) < 0)
        err_sys("open error");


    exit(0);
}