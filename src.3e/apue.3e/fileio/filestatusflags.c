/* Write a program that opens a file using some particular set of file status flags. Query the file status flags and print the file status (using fcntl). Repeat test with different set of file status flags.*/

#include "apue.h"
#include <fcntl.h>

int main()
{
	int fd, val;

	if ((fd = open("status.txt", O_SYNC)) < 0)
		err_sys("open error");

	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl error for fd %d", fd);

	/*Access Modes*/
	switch (val & O_ACCMODE)
	{
	case O_RDONLY:
		printf("read only | ");
		break;

	case O_WRONLY:
		printf("write only | ");
		break;

	case O_RDWR:
		printf("read write | ");
		break;

	default:
		err_dump("unknown access mode");
	}

	if (val & O_APPEND)
		printf("append | ");
	if (val & O_NONBLOCK)
		printf("nonblocking | ");
	if (val & O_SYNC)
		printf("synchronous writes | ");
	if (val & O_DSYNC)
		printf("synchronous data writes | ");
	if (val & O_RSYNC)
		printf("synchronous reads and writes | ");

	putchar('\n');
	exit(0);
}