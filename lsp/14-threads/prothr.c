/*
 * =====================================================================================
 *
 *       Filename:  prothr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月30日 21时25分31秒
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

#include <pthread.h>
#include <unistd.h>
#include <wait.h>

pthread_mutex_t mutex;

void *another(void *arg)
{
        printf("in child thread, lock the mutex.\n");
        pthread_mutex_lock(&mutex);
        sleep(5);
        pthread_mutex_unlock(&mutex);

        return NULL;
}

void prepare()
{
        pthread_mutex_lock(&mutex);
}

void infork()
{
        pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
	pthread_mutex_init(&mutex, NULL);
        pthread_t id;
        pthread_create(&id, NULL, another, NULL);
        sleep(1);
        pthread_atfork(prepare, infork, infork);
        int pid = fork();
        if (pid < 0) {
                pthread_join(id, NULL);
                pthread_mutex_destroy(&mutex);
                return 1;
        } else if (pid == 0) {
                printf("I am in the child, want to get the lock.\n");
                pthread_mutex_lock(&mutex);
                printf("I can not run to here, oop...\n");
                pthread_mutex_unlock(&mutex);
                exit(0);
        } else {
                wait(NULL);
        }
        pthread_join(id, NULL);
        pthread_mutex_destroy(&mutex);

	return EXIT_SUCCESS;
}
