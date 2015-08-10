/*
 * =====================================================================================
 *
 *       Filename:  testthread.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 19时52分12秒
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

int     globval = 0;
pthread_mutex_t mutex;
pthread_cond_t  cond;

void *thread1(void *arg)
{
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        globval++;
        printf("In thread1, globval = %d\n", globval);
        pthread_mutex_unlock(&mutex);
        return NULL;
}

void *thread2(void *arg)
{
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        globval++;
        printf("In thread1, globval = %d\n", globval);
        pthread_mutex_unlock(&mutex);
        return NULL;
}

void *thread3(void *arg)
{
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        globval++;
        printf("In thread1, globval = %d\n", globval);
        pthread_mutex_unlock(&mutex);
        return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t       thid[3] = { 0 };
        typedef void *(*th_fun)(void *);
        th_fun          t_fun[3] = {thread1, thread2, thread3};
        int     i;

        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&cond, NULL);
        for (i = 0; i < 3; i++)
                pthread_create(&thid[i], NULL, (void *)t_fun[i], NULL);
        do {
                pthread_cond_signal(&cond);
        } while ( 1 );
        sleep(1);
        pthread_exit(0);

	return EXIT_SUCCESS;
}
