/* ***********************************************************************

  > File Name: getcwd.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 28 Dec 2017 11:39:17 AM CST

 ********************************************************************** */

#include <stdio.h>
#include "../../apue.h"
#include <errno.h>
#include <string.h>

int main(int argc, const char* argv[])
{
    char buf[256];
    printf("pwd: %s\n", getcwd(buf, 256));
    printf("err: %s\n", strerror(errno));
    /*if (chdir("/tmp") < 0)*/
        /*err_sys("chdir failed");*/
    /*printf("chdir to /tmp succeed\n");*/
    /*printf("pwd: %s\n", getcwd(buf, 32));*/

    return 0;
}
