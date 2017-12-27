/* ***********************************************************************

  > File Name: t_unlink.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Wed 27 Dec 2017 03:04:26 PM CST

 ********************************************************************** */

#include <stdio.h>
#include "../../apue.h"
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    if (open("tempfile", O_RDWR) < 0)
        err_sys("open error");
    if (unlink("tempfile") < 0)
        err_sys("unlink error");
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");

    return 0;
}
