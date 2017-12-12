/* ***********************************************************************

  > File Name: t_vfork.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Wed 06 Dec 2017 04:02:56 PM CST

 ********************************************************************** */

#include "../../apue.h"

int glob = 6;

int main(int argc, const char* argv[])
{
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");
    if ((pid = vfork()) < 0) {
        err_sys("vfork error");
    } else if (pid == 0) {
        glob++;
        var++;
        /*_exit(0);*/
        exit(0);
    }

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    return 0;
}
