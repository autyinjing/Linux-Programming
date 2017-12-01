/*
 * =====================================================================================
 *
 *       Filename:  10.13.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月28日 12时14分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

Sigfunc *signal_intr( int signo, Sigfunc *func )
{
	struct sigaction 	act, oact;

	act.sa_restorer = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
#ifdef SA_INTERRUPT
	act.saflags |= SA_INTERRUPT;
#endif
	if ( sigaction(signo, &act, &oact) < 0 )
	      return (SIG_ERR);
	return (oact.sa_restorer);
}
