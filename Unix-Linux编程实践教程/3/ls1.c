/* ***********************************************************************

  > File Name: ls1.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月14日 星期三 15时08分14秒

 ********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

#include "../Common.hpp"

void do_ls(const char[]);

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

void do_ls(const char dirname[])
{
    DIR *dir_ptr;
    struct dirent *direntp;

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls1: cannot open %s\n", dirname);
    } else {
        while ((direntp = readdir(dir_ptr)) != NULL)
            printf("%s\n", direntp->d_name);
        closedir(dir_ptr);
    }
}
