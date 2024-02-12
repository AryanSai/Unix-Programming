#include "apue.h"
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char *permission_string(struct stat buf)
{
    static char perms[11];       /*one extra for terminator*/
    strcpy(perms, "----------"); /*default*/
    if (S_ISREG(buf.st_mode))
        perms[0] = '-';
    else if (S_ISDIR(buf.st_mode))
        perms[0] = 'd';
    else if (S_ISCHR(buf.st_mode))
        perms[0] = 'c';
    else if (S_ISBLK(buf.st_mode))
        perms[0] = 'b';
    else if (S_ISFIFO(buf.st_mode))
        perms[0] = 'p';
    else if (S_ISLNK(buf.st_mode))
        perms[0] = 'l';
    else if (S_ISSOCK(buf.st_mode))
        perms[0] = 's';
    /*owner permissions*/
    if (buf.st_mode & S_IRUSR)
        perms[1] = 'r';
    if (buf.st_mode & S_IWUSR)
        perms[2] = 'w';
    if (buf.st_mode & S_IXUSR)
        perms[3] = 'x';
    /*group permissions*/
    if (buf.st_mode & S_IRGRP)
        perms[4] = 'r';
    if (buf.st_mode & S_IWGRP)
        perms[5] = 'w';
    if (buf.st_mode & S_IXGRP)
        perms[6] = 'x';
    /*other permissions*/
    if (buf.st_mode & S_IROTH)
        perms[7] = 'r';
    if (buf.st_mode & S_IWOTH)
        perms[8] = 'w';
    if (buf.st_mode & S_IXOTH)
        perms[9] = 'x';

    return perms;
}

void printInfo(const char *filename, struct stat buf, int n)
{
    struct passwd *pw = getpwuid(buf.st_uid);
    struct group *gr = getgrgid(buf.st_gid);
    printf("%-10s ", permission_string(buf));
    printf("%3ld ", buf.st_nlink);
    if (n != 1)
        printf("%-5s ", pw->pw_name);
    else
        printf("%-5d ", buf.st_uid);
    if (n != 1)
        printf("%-5s ", gr->gr_name);
    else
        printf("%-5d ", buf.st_gid);
    printf("%6ld ", buf.st_size);
    printf("%.12s ", ctime(&buf.st_mtim.tv_sec) + 4);

    if (S_ISDIR(buf.st_mode)) {
        printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n", filename);
    } else {
        printf("%s\n", filename);
    }
}

void printDir(struct stat buf, const char *name, int n, int hidden)
{
    DIR *dp;
    struct dirent *dirp;
    char full_path[50];

    printf("total: %ld\n", buf.st_blocks);
    if ((dp = opendir(name)) == NULL)
        err_sys("can't open %s", name);

    while ((dirp = readdir(dp)) != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", name, dirp->d_name);

        if (stat(full_path, &buf) < 0)
            err_ret("stat error for %s", full_path);
        else if (hidden == 1 && dirp->d_name[0] == '.')
            printInfo(dirp->d_name, buf, n);
        else if (hidden == 0 && dirp->d_name[0] == '.')
            continue;
        else
            printInfo(dirp->d_name, buf, n);
    }
    closedir(dp);
}

int main(int argc, char *argv[])
{
    struct stat buf;
    char *option = argv[1];

    if (argc != 3)
    {
        printf("Usage: %s [-a] [-l] [-n] [-d] <directory_path>\n", argv[0]);
        return 1;
    }

    if (strcmp(option, "-a") == 0)
        printDir(buf, argv[2], 0, 1);
    else if (strcmp(option, "-l") == 0)
        printDir(buf, argv[2], 0, 0);
    else if (strcmp(option, "-n") == 0)
        printDir(buf, argv[2], 1, 0);
    else if (strcmp(option, "-d") == 0)
    {
        if (stat(argv[2], &buf) < 0)
            err_ret("stat error for %s", argv[2]);
        else
            printInfo(argv[2], buf, 0);
    }
    else
        printf("Invalid option: %s\n", option);

    exit(0);
}