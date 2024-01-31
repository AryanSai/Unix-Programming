/*Write a program called issymlink that takes a filename as an argument and checks whether the filename is a symbolic link. If so, it should read the symbolic link file (and not the file pointed to by the symbolic link) and print its contents to stdout. Else it just prints a message saying passed filename is not a symbolic link.*/

#include "apue.h"

int main(int argc, char *argv[])
{
	struct stat buf;
	char buffer[256]; /*buffer for reading the file*/

	/*get the stat of the file*/
	if (lstat(argv[1], &buf) < 0)
		err_ret("lstat error");

	/*check if the file is a symbolic link*/
	if (S_ISLNK(buf.st_mode))
	{
		printf("The file is a symbolic link!!\n");

		/*read the file; cannot use open since it follows the symbolic link*/
		ssize_t len = readlink(argv[1], buffer, sizeof(buffer) - 1);
		if (len != -1)
		{
			buffer[len] = '\0'; /*readLink does not terminate with null*/
			printf("Contents of the symbolic link file: %s\n", buffer);
		}
		else
		{
			perror("readlink error!!");
			return 1;
		}
	}
	else
		printf("The file is not a symbolic link!!\n");

	exit(0);
}
