/*
 * =====================================================================================
 *
 *       Filename:  prime.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 21时58分16秒
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
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

enum    { MAXN = 1000000000 };
bool    flag[MAXN];
int     primes[MAXN / 7], pi;

void GetPrime_1()
{
        int     i, j;
        pi = 0;
        memset(flag, false, sizeof(flag));
        for (i = 2; i < MAXN; i++)
                if ( !flag[i] )
                {
                        primes[pi++] = i;
                        for (j = i; j < MAXN; j += i)
                                flag[j] = true;
                }
}

void GetPrime_2()
{
        int     i, j;
        pi = 0;
        memset(flag, false, sizeof(flag));
        for (i = 2; i < MAXN; i++)
        {
                if ( !flag[i] )
                        primes[pi++] = i;
                for (j = 0; (j < pi) && (i * primes[j] < MAXN); j++)
                {
                        flag[i * primes[j]] = true;
                        if (i % primes[j] == 0)
                                break;
                }
        }
}

int main(int argc, char *argv[])
{
        printf("效率对比\n");
        clock_t         clockBegin, clockEnd;

        clockBegin = clock();
        GetPrime_1();
        clockEnd = clock();
        printf("普通筛素数方法  \t%lu毫秒\n", clockEnd - clockBegin);

        clockBegin = clock();
        GetPrime_2();
        clockEnd = clock();
        printf("改进的筛素数方法\t%lu毫秒\n", clockEnd - clockBegin);

	return EXIT_SUCCESS;
}
