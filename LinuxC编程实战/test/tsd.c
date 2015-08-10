/*
 * =====================================================================================
 *
 *       Filename:  tsd.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 13时07分24秒
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

pthread_key_t   key;

void *thread2(void *arg)
{
        int     tsd = 5;
        printf("thread %lu is running\n", pthread_self());
        pthread_setspecific(key, &tsd);
        printf("thread %lu returns %d\n", pthread_self(), *(int *)(pthread_getspecific(key)));

        return NULL;
}

void *thread1(void *arg)
{
        int     tsd = 0;
        pthread_t       thid2;

        printf("thread %lu is running\n", pthread_self());
        pthread_setspecific(key, &tsd);
        pthread_create(&thid2, NULL, thread2, NULL);
        sleep(3);
        printf("thread %lu returns %d\n", pthread_self(), *(int *)(pthread_getspecific(key)));

        return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t       thid1;

        printf("main thread begins running\n");
        pthread_key_create(&key, NULL);
        pthread_create(&thid1, NULL, thread1, NULL);
        sleep(5);
        pthread_key_delete(key);
        printf("main thread exit\n");
 
        pthread_exit(0);
}
