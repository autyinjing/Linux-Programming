/*
 * =====================================================================================
 *
 *       Filename:  fork3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 12时51分41秒
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
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        pid_t   pid;

        pid = fork();
        switch (pid)
        {
                case 0:
                        while ( 1 )
                        {
                                sleep(3);
                                printf("A background process, PID: %d, ParentID: %d\n",
                                                getpid(), getppid());
                        }
                case -1:
                        perror("Process creation failed\n");
                        break;
                default:
                        printf("I am parent, my pid is %d\n", getpid());
                        exit(0);
        }

	return EXIT_SUCCESS;
}
