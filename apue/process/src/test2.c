/* ***********************************************************************

  > File Name: test2.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Tue 05 Dec 2017 10:17:17 AM CST

 ********************************************************************** */

#include <stdio.h>
#include "../../apue.h"

static void pr_ids(char *name)
{
    printf("%s: pid = %d, ppid = %d, pgrp = %d, sid = %d, tpgrp = %d\n", 
        name, getpid(), getppid(), getpgrp(), getsid(0), tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main(int argc, const char* argv[])
{
    pid_t pid;
    /*char c;*/

    pr_ids("parent");
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        sleep(5);
        exit(0);
    } else {
        pr_ids("child 1");
        setsid();
        pr_ids("child 2");
        /*if (read(STDIN_FILENO, &c, 1) != 1)*/
            /*printf("read error from controlling TTY, errno = %d\n", errno);*/
        exit(0);
    }

    return 0;
}
