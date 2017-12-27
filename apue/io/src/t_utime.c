/* ***********************************************************************

  > File Name: t_utime.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Wed 27 Dec 2017 04:19:58 PM CST

 ********************************************************************** */

#include <stdio.h>
#include "../../apue.h"
#include <utime.h>
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    int             i, fd;
    struct stat     statbuf;
    struct utimbuf  timebuf;

    for (i = 1; i < argc; ++i)
    {
        if (stat(argv[i], &statbuf) < 0) {
            err_ret("%s: stat error", argv[1]);
            continue;
        }
        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
            err_ret("%s: open error", argv[i]);
            continue;
        }
        close(fd);
        timebuf.actime = statbuf.st_atime;
        timebuf.modtime = statbuf.st_mtime;
        /*if (utime(argv[i], &timebuf) < 0) {*/
            /*err_ret("%s: utime error", argv[i]);*/
            /*continue;*/
        /*}*/
    }

    return 0;
}
