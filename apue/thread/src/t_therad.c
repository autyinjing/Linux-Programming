/* ***********************************************************************

  > File Name: t_therad.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 25 Jan 2018 03:26:44 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define TIMES 20

int a = 0;

pthread_mutex_t lock_1 = PTHREAD_MUTEX_INITIALIZER;
/*pthread_mutex_t lock_2 = PTHREAD_MUTEX_INITIALIZER;*/

/*int count[4] = {0, 0, 0, 0};*/
pthread_mutex_t t_lock[4] = 
{
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
};

void *thr_fna(void *data)
{
    int idx = *(int *)data;
    while (a < TIMES)
    {
        int i = 1;
        for (; i <= 4; ++i)
        {
            pthread_mutex_lock(&lock_1);
            int tmp = a % 4 + 1;
            if (tmp == idx)
                printf("thread %d, a = %d\n", idx, ++a);
            pthread_mutex_unlock(&lock_1);
        }
    }
    return NULL;
}

void *thr_fn1(void *data)
{
    int idx = *(int *)data;
    while (a < TIMES)
    {
        pthread_mutex_lock(&lock_1);
        int i = 1;
        for (; i <= 4; ++i)
        {
            pthread_mutex_lock(&t_lock[i-1]);
            int tmp = a % 4 + 1;
            if (tmp == idx)
                printf("thread %d, a = %d\n", idx, ++a);
            pthread_mutex_unlock(&t_lock[i-1]);
        }
        pthread_mutex_unlock(&lock_1);
    }
    return NULL;
}

void *thr_fn2(void *data)
{
    int idx = *(int *)data;
    while (a < TIMES)
    {
        pthread_mutex_lock(&lock_1);
        int i = 1;
        for (; i <= 4; ++i)
        {
            pthread_mutex_lock(&t_lock[i-1]);
            int tmp = a % 4 + 1;
            if (tmp == idx)
                printf("thread %d, a = %d\n", idx, ++a);
            pthread_mutex_unlock(&t_lock[i-1]);
        }
        pthread_mutex_unlock(&lock_1);
    }
    return NULL;
}

void *thr_fn3(void *data)
{
    int idx = *(int *)data;
    while (a < TIMES)
    {
        pthread_mutex_lock(&lock_1);
        int i = 1;
        for (; i <= 4; ++i)
        {
            pthread_mutex_lock(&t_lock[i-1]);
            int tmp = a % 4 + 1;
            if (tmp == idx)
                printf("thread %d, a = %d\n", idx, ++a);
            pthread_mutex_unlock(&t_lock[i-1]);
        }
        pthread_mutex_unlock(&lock_1);
    }
    return NULL;
}

void *thr_fn4(void *data)
{
    int idx = *(int *)data;
    while (a < TIMES)
    {
        pthread_mutex_lock(&lock_1);
        int i = 1;
        for (; i <= 4; ++i)
        {
            pthread_mutex_lock(&t_lock[i-1]);
            int tmp = a % 4 + 1;
            if (tmp == idx)
                printf("thread %d, a = %d\n", idx, ++a);
            pthread_mutex_unlock(&t_lock[i-1]);
        }
        pthread_mutex_unlock(&lock_1);
    }
    return NULL;
}

/*void *thr_fn1(void *data)*/
/*{*/
    /*while (a < TIMES)*/
    /*{*/
        /*pthread_mutex_lock(&lock_1);*/
        /*if (a & 1)*/
        /*{*/
            /*++a;*/
            /*printf("thread 1 a = %d\n", a);*/
        /*}*/
        /*pthread_mutex_unlock(&lock_1);*/
    /*}*/
    /*return NULL;*/
/*}*/

/*void *thr_fn2(void *data)*/
/*{*/
    /*while (a < TIMES)*/
    /*{*/
        /*pthread_mutex_lock(&lock_1);*/
        /*if (!(a & 1))*/
        /*{*/
            /*++a;*/
            /*printf("thread 2 a = %d\n", a);*/
        /*}*/
        /*pthread_mutex_unlock(&lock_1);*/
    /*}*/
    /*return NULL;*/
/*}*/

typedef void *(*th_fn_t)(void *);

int main(int argc, const char* argv[])
{
    pthread_t tid[4];
    th_fn_t thr_fn[4] = {thr_fn1, thr_fn2, thr_fn3, thr_fn4};

    int i = 1;
    for (; i <= 4; ++i)
        /*pthread_create(&tid[i-1], NULL, thr_fn[i-1], (void *)&i);*/
        pthread_create(&tid[i-1], NULL, thr_fna, (void *)&i);

    for (i = 1; i <= 4; ++i)
        pthread_join(tid[i-1], NULL);

    return 0;
}

/*int a = 0;*/

/*void *thr_fn1(void *arg)*/
/*{*/
    /*int idx = *((int *)arg);*/
    /*++a;*/
    /*printf("thread %d a = %d\n", idx, a);*/
    /*if (a >= TIMES)*/
        /*[>pthread_exit((void *)idx);<]*/
        /*return (void *)idx;*/
    /*return (void *)0;*/
/*}*/

/*void *thr_fn2(void *arg)*/
/*{*/
    /*printf("thread 2 a = %d\n", a);*/
    /*++a;*/
    /*if (a >= TIMES)*/
        /*pthread_exit((void *)2);*/
    /*return (void *)0;*/
/*}*/

/*void *thr_fn3(void *arg)*/
/*{*/
    /*printf("thread 3 a = %d\n", a);*/
    /*++a;*/
    /*if (a >= TIMES)*/
        /*pthread_exit((void *)3);*/
    /*return (void *)0;*/
/*}*/

/*void *thr_fn4(void *arg)*/
/*{*/
    /*printf("thread 4 a = %d\n", a);*/
    /*++a;*/
    /*if (a >= TIMES)*/
        /*pthread_exit((void *)4);*/
    /*return (void *)0;*/
/*}*/

/*int main(int argc, const char* argv[])*/
/*{*/
    /*[>pthread_t tid1, tid2, tid3, tid4;<]*/
    /*pthread_t tid[4];*/

    /*void *pRet;*/
    /*while ( 1 )*/
    /*{*/
        /*int i = 1, flag = 0;*/
        /*for (; i <= 4; ++i)*/
        /*{*/
            /*pthread_create(&tid[i-1], NULL, thr_fn1, (void *)&i);*/
            /*pthread_join(tid[i-1], &pRet);*/
            /*if ((int)pRet > 0)*/
                /*flag = 1;*/
        /*}*/

        /*if (flag)*/
            /*break;*/

        /*[>pthread_create(&tid2, NULL, thr_fn2, NULL);<]*/
        /*[>pthread_join(tid2, &pRet);<]*/
        /*[>if ((int)pRet > 0)<]*/
            /*[>break;<]*/

        /*[>pthread_create(&tid3, NULL, thr_fn3, NULL);<]*/
        /*[>pthread_join(tid3, &pRet);<]*/
        /*[>if ((int)pRet > 0)<]*/
            /*[>break;<]*/

        /*[>pthread_create(&tid4, NULL, thr_fn4, NULL);<]*/
        /*[>pthread_join(tid4, &pRet);<]*/
        /*[>if ((int)pRet > 0)<]*/
            /*[>break;<]*/
    /*}*/

    /*return 0;*/
/*}*/
