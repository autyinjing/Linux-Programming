/*
 * =====================================================================================
 *
 *       Filename:  10-18.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月04日 12时40分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void abort( void )
{
	sigset_t 		mask;
	struct sigaction 	action;

	sigaction(SIGABRT, NULL, &action);
	if ( action.sa_restorer == SIG_IGN ) {
		action.sa_restorer = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	}
	if ( action.sa_restorer == SIG_DFL )
	      fflush(NULL);

	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);

	fflush(NULL);
	action.sa_restorer = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	exit(1);
}
