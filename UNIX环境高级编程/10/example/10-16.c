/*
 * =====================================================================================
 *
 *       Filename:  10-16.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月03日 14时12分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

volatile sig_atomic_t 	quitflag;

static void sig_int( int signo )
{
	if ( signo == SIGINT )
	      printf("\ninterrupt\n");
	else if ( signo == SIGQUIT )
	      quitflag = 1;
}

int main( int argc, char *argv[] )
{
	sigset_t 	newmask, oldmask, zeromask;

	if ( signal(SIGINT, sig_int) == SIG_ERR )
	      err_sys("signal(SIGINT) error");
	if ( signal(SIGQUIT, sig_int) == SIG_ERR )
	      err_sys("signal(SIGQUIT) error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	if ( sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0 )
	      err_sys("SIG_BLOCK error");

	while ( quitflag == 0 )
	      sigsuspend(&zeromask);

	quitflag = 0;

	if ( sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0 )
	      err_sys("SIG_SETMASK error");

	exit(0);
}
