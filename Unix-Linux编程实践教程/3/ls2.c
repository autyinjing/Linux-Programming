/* ***********************************************************************

  > File Name: ls2.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月14日 星期三 16时16分23秒

 ********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

void do_ls(const char*);
void dostat(const char*);
void show_file_info(const char*, struct stat*);
void mode_to_letters(int, char*);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc, const char* argv[])
{
    if (argc == 1) {
        do_ls(".");
    } else {
        while (--argc)
        {
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }
    }

    return 0;
}

void do_ls(const char *dirname)
{
    DIR *dir_ptr;
    struct dirent *direntp;

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls2:cannot open %s\n", dirname);
    } else {
        printf("%s:\n", dirname);
        while ((direntp = readdir(dir_ptr)) != NULL)
            dostat(direntp->d_name);
        closedir(dir_ptr);
    }
}

void dostat(const char *filename)
{
    struct stat info;
    if (stat(filename, &info) == -1)
        perror(filename);
    else
        show_file_info(filename, &info);
}

void show_file_info(const char *filename, struct stat *info_p)
{
    char modestr[11];

    mode_to_letters(info_p->st_mode, modestr);

    printf("%s", modestr);
    printf(" %2d", (int)info_p->st_nlink);
    printf(" %-5s", uid_to_name(info_p->st_uid));
    printf(" %-5s", gid_to_name(info_p->st_gid));
    printf(" %6ld", (long)info_p->st_size);
    printf(" %.12s", 4+ctime(&info_p->st_mtime));
    printf(" %s\n", filename);
}

void mode_to_letters(int mode, char *str)
{
    strcpy(str, "----------");

    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}

#include <pwd.h>

char *uid_to_name(uid_t uid)
{
    struct passwd *getpwuid(), *pw_ptr;
    static char number[10];

    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(number, "%d", uid);
        return number;
    } else {
        return pw_ptr->pw_name;
    }
}

#include <grp.h>

char *gid_to_name(gid_t gid)
{
    struct group *getgrgid(), *grp_ptr;
    static char numstr[10];

    if ((grp_ptr = getgrgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    } else {
        return grp_ptr->gr_name;
    }
}
