/*
 * =====================================================================================
 *
 *       Filename:  testtf.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 20时10分14秒
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
#include <pthread.h>
#include <unistd.h>

void *thread1(void *arg)
{
        printf("In process %d, thread %lu\n", getpid(), pthread_self());
        return NULL;
}

void *thread2(void *arg)
{
        printf("In process %d, thread %lu\n", getpid(), pthread_self());
        return NULL;
}


int main(int argc, char *argv[])
{
	int     i, k;
        pthread_t       thid[8];
        pid_t   pid[4];

        for (i = 0, k = 0; i < 4; i++)
        {
                pid[i] = fork();
                switch (pid[i])
                {
                        case 0:
                                pthread_create(&thid[k++], NULL, thread1, NULL);
                                pthread_create(&thid[k++], NULL, thread2, NULL);
                                exit(0);
                        case -1:
                                printf("fork error\n");
                                exit(-1);
                        default:
                                printf("PID = %d\n", pid[i]);
                                sleep(1);
                                break;
                }
        }
        pthread_exit(0);

	return EXIT_SUCCESS;
}
