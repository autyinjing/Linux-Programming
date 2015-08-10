/*
 * =====================================================================================
 *
 *       Filename:  10-12.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月28日 12时08分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

Sigfunc *signal( int signo, Sigfunc *func )
{
	struct sigaction 	act, oact;

	act.sa_restorer = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if ( signo == SIGALRM ) {
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	} else {
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif
	}
	if ( sigaction(signo, &act, &oact) < 0 )
	      return (SIG_ERR);
	return (oact.sa_restorer);
}
