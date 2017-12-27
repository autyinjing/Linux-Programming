/* ***********************************************************************

  > File Name: t_umask.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Wed 27 Dec 2017 11:30:21 AM CST

 ********************************************************************** */

#include <stdio.h>
#include "../../apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(int argc, const char* argv[])
{
    umask(0);
    if (creat("foo", RWRWRW) < 0)
        err_sys("create error for foo");
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0)
        err_sys("creat error for bar");

    return 0;
}
