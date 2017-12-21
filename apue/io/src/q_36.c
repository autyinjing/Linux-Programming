/* ***********************************************************************

  > File Name: q_36.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 21 Dec 2017 10:35:43 AM CST

 ********************************************************************** */

#include <stdio.h>
#include "../../apue.h"
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    int fd = open("a.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd < 0)
        err_sys("open 1 error");

    if (write(fd, "abcdefg, hijklmn?", 18) < 18)
        err_sys("write 2 error");
    close(fd);

    fd = open("a.txt", O_RDONLY | O_APPEND);
    if (fd < 0)
        err_sys("open 2 error");

    if (lseek(fd, 5, SEEK_SET) < 0)
        err_sys("lseek error");
    char buf[16] = {0};
    if (read(fd, buf, 1) < 1)
        err_sys("read error");
    printf("%s\n", buf);
    /*if (write(fd, "x", 1) < 1)*/
        /*err_sys("write 2 error");*/
    close(fd);

    return 0;
}
