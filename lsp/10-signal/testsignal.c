/*
 * =====================================================================================
 *
 *       Filename:  testsignal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月18日 11时53分43秒
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
#include <signal.h>

/* 信号处理函数 */
void sig_handler(int sig)
{
        printf("Recvied a signal of %d\n", sig);
}

int main(int argc, char *argv[])
{
	signal(SIGHUP, sig_handler);
        signal(SIGCHLD, sig_handler);
        signal(SIGTERM, sig_handler);
        signal(SIGINT, sig_handler);

        while ( 1 )
                ;

	return EXIT_SUCCESS;
}

