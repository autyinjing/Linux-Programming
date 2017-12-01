/*
 * =====================================================================================
 *
 *       Filename:  10-21.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月04日 13时01分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

static void sig_alrm( int signo )
{
}

unsigned int sleep( unsigned int nsecs )
{
	struct sigaction 	newact, oldact;
	sigset_t 		newmask, oldmask, suspmask;
	unsigned int 		unslept;

	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	alarm(nsecs);

	suspmask = oldmask;
	sigdelset(&suspmask, SIGALRM);
	sigsuspend(&suspmask);

	unslept = alarm(0);
	sigaction(SIGALRM, &oldact, NULL);

	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return (unslept);
}

int main( int argc, char *argv[] )
{
	sleep(atoi(argv[1]));

	exit(0);
}
