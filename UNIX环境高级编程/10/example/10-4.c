/*
 * =====================================================================================
 *
 *       Filename:  10-4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月27日 16时51分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void sig_alrm( int signo )
{
}

unsigned int sleep1( unsigned int nsecs )
{
	if ( signal(SIGALRM, sig_alrm) == SIG_ERR )
	      return (nsecs);
	alarm(nsecs);
	pause();
	return (alarm(0));
}

int main( int argc, char *argv[] )
{
	sleep1(atoi(argv[1]));

	exit(0);
}
