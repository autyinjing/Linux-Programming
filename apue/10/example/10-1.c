/*
 * =====================================================================================
 *
 *       Filename:  10-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月27日 16时24分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

static void 	sig_usr( int );

int main( int argc, char *argv[] )
{
	if ( signal(SIGUSR1, sig_usr) == SIG_ERR )
	      err_sys("can't catch SIGUSR1");
	if ( signal(SIGUSR2, sig_usr) == SIG_ERR )
	      err_sys("can't catch SIGUSR2");
	for ( ; ; )
	      pause();

	exit(0);
}

static void sig_usr( int signo )
{
	if ( signo == SIGUSR1 )
	      printf("received SIGUSR1\n");
	else if ( signo == SIGUSR2 )
	      printf("received SIGUSR2\n");
	else
	      err_dump("received signal %d\n", signo );
}
