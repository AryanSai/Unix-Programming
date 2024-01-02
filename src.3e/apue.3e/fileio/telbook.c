#include "apue.h"
#include <fcntl.h>
#include <stdio.h>

#define ENTRY_SIZE 40

void create_telbook(char telbook_name[])
{
	int size;
	printf("Enter the size of the telbook: ");
	scanf("%d", &size);

	off_t file_size = size * ENTRY_SIZE;

	int fd;
	if ((fd = creat(telbook_name, FILE_MODE)) < 0)
		err_sys("creat error");

	if (lseek(fd, file_size - 1, SEEK_SET) == -1)
		err_sys("lseek error");

	if (write(fd, "", 1) != 1)
		err_sys("write error");
}

void create_entry(char telbook_name[])
{
	int fd = open(telbook_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

	int index_num;

	char tel_name[20] = "", tel_num[20] = "";

	printf("Enter the index number: ");
	scanf("%d", &index_num);

	printf("Enter the Name: ");
	scanf("%s", tel_name);

	printf("Enter the Number: ");
	scanf("%s", tel_num);

	if (lseek(fd, (index_num - 1) * ENTRY_SIZE, SEEK_SET) == -1)
		err_sys("lseek error");

	if (write(fd, tel_name, 20) != 20)
		err_sys("write error for name");

	if (write(fd, tel_num, 20) != 20)
		err_sys("write error for telephone number");
	close(fd);
}

void display_entry(char telbook_name[])
{
	int fd = open(telbook_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

	int index_num;

	char tel_name[20], tel_num[20];

	printf("Enter the index number to display: ");
	scanf("%d", &index_num);

	if (lseek(fd, (index_num - 1) * ENTRY_SIZE, SEEK_SET) == -1)
		err_sys("lseek error");

	if (read(fd, tel_name, 20) != 20)
		err_sys("read error for name");

	if (read(fd, tel_num, 20) != 20)
		err_sys("read error for telephone number");

	printf("Entry at index %d:\n", index_num);
	printf("Name: %s\n", tel_name);
	printf("Telephone Number: %s\n", tel_num);
	close(fd);
}

int main()
{
	int option;
	char telbook_name[30] = "";
	printf("1. Create a new telbook\n2. Open an existing telbook\nEnter your Option:");
	scanf("%d", &option);
	if (option == 1)
	{
		printf("Enter the name of the telbook: ");
		scanf("%s", telbook_name);
		create_telbook(telbook_name);
	}
	else if (option == 2)
	{
		printf("Enter the name of the telbook: ");
		scanf("%s", telbook_name);
	}
	else
	{
		printf("Enter a valid option!!");
		exit(0);
	}

	while (1)
	{
		printf("\n1. Create an entry\n2. Display an entry\nEnter your option:");
		scanf("%d", &option);
		if (option == 1)
			create_entry(telbook_name);
		else if (option == 2)
			display_entry(telbook_name);
		else
		{
			printf("Enter a valid option!!");
			break;
		}
	}

	exit(0);
}
