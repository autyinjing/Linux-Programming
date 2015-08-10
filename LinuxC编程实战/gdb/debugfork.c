/*
 * =====================================================================================
 *
 *       Filename:  debugfork.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 19时58分32秒
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

int main(int argc, char *argv[])
{
        pid_t   pid;
        int     status;

        if ((pid = fork()) < 0) {
                perror("fork");
                exit(-1);
        } else if (pid == 0) {
                int     i, sum = 0;
                for (i = 0; i < 100; i++)
                        sum += i;
                printf("sum = %d\n", sum);
                exit(2);
        } else {
                wait(&status);
                printf("status = %d\n", status);
                exit(0);
        }

	return EXIT_SUCCESS;
}
