/*
 * =====================================================================================
 *
 *       Filename:  fork2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 20时44分58秒
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
        char    *msg;
        int     k;

        printf("Process Creation Study\n");
        pid = fork();
        switch ( pid )
        {
                case 0:
                        msg = "Child process is running";
                        k = 3;
                        break;
                case -1:
                        perror("Process creation failed\n");
                        break;
                default:
                        msg = "Parent process is running";
                        k = 5;
                        break;
        }

        while (k > 0)
        {
                puts(msg);
                sleep(1);
                k--;
        }

	exit(0);
}
