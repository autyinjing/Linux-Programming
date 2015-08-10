/*
 * =====================================================================================
 *
 *       Filename:  testgettime.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月08日 12时52分51秒
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
#include <sys/time.h>

double timediff(struct timeval *begin, struct timeval *end)
{
        int     n;
        n = (end->tv_sec - begin->tv_sec) * 1000000 + (end->tv_usec - begin->tv_usec);

        return (double)(n) / 1000;
}

int main(int argc, char *argv[])
{
	struct timeval begin, end;

        gettimeofday(&begin, 0);

        printf("do something here...\n");
        sleep(1);

        gettimeofday(&end, 0);

        printf("running time: %lfms\n", timediff(&begin, &end));

	return EXIT_SUCCESS;
}

