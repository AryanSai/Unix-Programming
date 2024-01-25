#include "apue.h"
#include <time.h>
int main(int argc, char *argv[])
{
    int i;
    struct stat buf;
    char *ptr;

    for (i = 1; i < argc; i++)
    {
        printf("File Information of %s: \n\n", argv[i]);
        if (stat("file1.txt", &buf) < 0)
        {
            err_ret("lstat error");
            continue;
        }
        if (S_ISREG(buf.st_mode))
            ptr = "regular";
        else if (S_ISDIR(buf.st_mode))
            ptr = "directory";
        else if (S_ISCHR(buf.st_mode))
            ptr = "character special";
        else if (S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if (S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if (S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if (S_ISSOCK(buf.st_mode))
            ptr = "socket";
        else
            ptr = "** unknown mode **";

        printf("File Type: %s\nInode Number: %ld\nDevice Number: %ld\nDevice Number for special files: %ld\nNumber of Links: %ld\nUser Id of Owner: %d\nGroup Id of Owner: %d\nSize: %ld\n", ptr, buf.st_ino, buf.st_dev, buf.st_rdev, buf.st_nlink, buf.st_uid, buf.st_gid, buf.st_size);
        printf("Last Access Time: %d\n", ctime(&buf.st_atim.tv_sec));
        printf("Last Modification Time: %d\n", ctime(&buf.st_mtim.tv_sec));
        printf("I/O Block Size: %ld\n", buf.st_blksize);
        printf("Number of Blocks allocated: %ld\n", buf.st_blocks);
        printf("----------------------------------------------\n");
    }
    exit(0);
}
