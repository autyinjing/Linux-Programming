/*
 * =====================================================================================
 *
 *       Filename:  exec.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 22时50分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), linuxeryinjing@gmail.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char **environ)
{
        pid_t   pid;
        int     status;

        if ((pid = fork()) < 0) {
                perror("fork");
                exit(-1);
        } else if (pid == 0) {
                execve("pro1", argv, environ+10);
                exit(0);
        }
        if ((pid = fork()) < 0) {
                perror("fork");
                exit(-1);
        } else if (pid == 0) {
                execve("pro2", argv, environ);
                exit(0);
        }

        wait(&status);
	exit(0);
}
