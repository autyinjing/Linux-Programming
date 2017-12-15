/* ***********************************************************************

  > File Name: t_fcntl.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Fri 15 Dec 2017 04:40:28 PM CST

 ********************************************************************** */

#include "../../apue.h"
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    int     val;

    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
        err_sys("fcntl error for fd %d", atoi(argv[1]));

    switch (val & O_ACCMODE)
    {
    case O_RDONLY:
        printf("read only");
        break;
    case O_WRONLY:
        printf("write only");
        break;
    case O_RDWR:
        printf("read write");
        break;
    default:
        err_dump("unknow access mode");
    }

    if (val & O_APPEND)
        printf(", append");
    if (val & O_NONBLOCK)
        printf(", nonblocking");
#if defined(O_SYNC)
    if (val & O_SYNC)
        printf(", synchronous writes");
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
    if (val & O_FSYNC)
        printf(", synchronous writes");
#endif
    putchar('\n');
    return 0;
}
