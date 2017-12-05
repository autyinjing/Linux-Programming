/* ***********************************************************************

  > File Name: session.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Fri 01 Dec 2017 04:56:32 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void printIds()
{
    printf("pid:%d ppid:%d gid:%d sid:%d\n", getpid(), getppid(), getpgid(0), getsid(0));
}

int main(int argc, const char* argv[])
{
    pid_t pid = fork();
    printIds();

    if (pid > 0) {
        wait(NULL);
        exit(0);
    }

    printIds();

    return 0;
}
