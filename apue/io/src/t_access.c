/* ***********************************************************************

  > File Name: t_access.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Wed 27 Dec 2017 10:45:56 AM CST

 ********************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "../../apue.h"

int main(int argc, const char* argv[])
{
    if (argc != 2)
        err_quit("Usage: a.out <pathname>");
    if (access(argv[1], R_OK) < 0)
        err_ret("access error for %s", argv[1]);
    else
        printf("read access OK\n");
    if (open(argv[1], O_RDONLY) < 0)
        err_ret("open error for %s", argv[1]);
    else
        printf("open for reading OK\n");

    return 0;
}
