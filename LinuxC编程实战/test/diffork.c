/*
 * =====================================================================================
 *
 *       Filename:  diffork.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 21时36分22秒
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

int     globVar = 5;

int main(int argc, char *argv[])
{	
        pid_t   pid;
        int     var = 1, i;

        printf("fork is diffirent with vfork\n");

        //pid = fork();
        pid = vfork();
        switch (pid)
        {
                case 0:
                        i = 3;
                        while (i-- > 0)
                        {
                                printf("Child process is running\n");
                                globVar++;
                                var++;
                                sleep(1);
                        }
                        printf("Child's globVar = %d, var = %d\n", globVar, var);
                        break;
                case -1:
                        perror("Process creation failed\n");
                        exit(0);
                default:
                        i = 5;
                        while (i-- > 0)
                        {
                                printf("Parent process is running\n");
                                globVar++;
                                var++;
                                sleep(1);
                        }
                        printf("Parent's globVar = %d, var = %d\n", globVar, var);
                        exit(0);
        }

	return EXIT_SUCCESS;
}
