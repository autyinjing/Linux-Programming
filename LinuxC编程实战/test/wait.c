/*
 * =====================================================================================
 *
 *       Filename:  wait.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 22时24分08秒
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
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{	
        pid_t   pid;
        char    *msg;
        int     k;
        int     exit_code;

        printf("Study how to get exit code\n");
        pid = fork();
        switch (pid)
        {
                case 0:
                        msg = "Child process is running";
                        k = 5;
                        exit_code = 37;
                        break;
                case -1:
                        perror("Process creation failed\n");
                        exit(1);
                default:
                        exit_code = 0;
                        break;
        }

        if (pid != 0) {
                int     stat_val;
                pid_t   child_pid;

                child_pid = wait(&stat_val);

                printf("Child process has exited, pid = %d\n", child_pid);
                if (WIFEXITED(stat_val)) {
                        printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
                } else {
                        printf("Child exited abnormolly!\n");
                }
        } else {
                while (k-- > 0)
                {
                        puts(msg);
                        sleep(1);
                }
        }

	exit(exit_code);
}
