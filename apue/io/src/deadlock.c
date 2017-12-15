/* ***********************************************************************

  > File Name: deadlock.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Fri 15 Dec 2017 02:26:22 PM CST

 ********************************************************************** */

#include "../../apue.h"
#include <fcntl.h>

static void lockabyte(const char *name, int fd, off_t offset)
{
    if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
        err_sys("%s:writew_lock error", name);
    printf("%s: got the lock, byte %ld\n", name, offset);
}

int main(int argc, const char* argv[])
{
    int     fd;
    pid_t   pid;

    if ((fd = creat("templock", FILE_MODE)) < 0)
        err_sys("create error");
    if (write(fd, "ab", 2) != 2)
        err_sys("write error");

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        lockabyte("child", fd, 0);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockabyte("child", fd, 1);
    } else {
        lockabyte("parent", fd, 1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent", fd, 0);
    }
    return 0;
}
