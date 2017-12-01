/*
 * =====================================================================================
 *
 *       Filename:  10-9.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月27日 17时31分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include <signal.h>
#include <errno.h>

#define SIGBAD(signo) 	( (signo) <= 0 || (signo) >= NSIG )

int sigaddset( sigset_t *set, int signo )
{
	if ( SIGBAD(signo) ) {
		errno = EINVAL;
		return (-1);
	}
	*set |= 1 << (signo - 1);
	return (0);
}

int sigdelset( sigset_t *set, int signo )
{
	if ( SIGBAD(signo) ) {
		errno = EINVAL;
		return (-1);
	}
	*set &= ~(1 << (signo - 1));
	return (0);
}

int sigismember( sigset_t *set, int signo )
{
	if ( SIGBAD(signo) ) {
		errno = EINVAL;
		return (-1);
	}
	return ((*set & (1 << (signo - 1))) != 0);
}
