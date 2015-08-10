/*
 * =====================================================================================
 *
 *       Filename:  dlock.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月30日 21时01分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>

int a = 0;
int b = 0;

pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;

void *another(void *arg)
{
        pthread_mutex_lock(&mutex_b);
        printf("in child thread, got mutex b, waiting for mutex a\n");
        sleep(5);
        ++b;
        pthread_mutex_lock(&mutex_a);
        b += a++;
        pthread_mutex_unlock(&mutex_a);
        pthread_mutex_unlock(&mutex_b);
        pthread_exit(NULL);
        return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t thid;

        pthread_mutex_init(&mutex_a, NULL);
        pthread_mutex_init(&mutex_b, NULL);
        pthread_create(&thid, NULL, another, NULL);

        pthread_mutex_lock(&mutex_a);
        printf("in parent thread, got mutex a, waiting for mutex b\n");
        sleep(5);
        ++a;
        pthread_mutex_lock(&mutex_b);
        a += b++;
        pthread_mutex_unlock(&mutex_b);
        pthread_mutex_unlock(&mutex_a);

        pthread_join(thid, NULL);
        pthread_mutex_destroy(&mutex_a);
        pthread_mutex_destroy(&mutex_b);

	return EXIT_SUCCESS;
}
