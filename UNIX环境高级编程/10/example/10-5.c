/*
 * =====================================================================================
 *
 *       Filename:  10-5.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月27日 16时57分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include <setjmp.h>

static jmp_buf 	env_alrm;
static void 	sig_int( int );

static void sig_alrm( int signo )
{
	longjmp(env_alrm, 1);
}

unsigned int sleep2( unsigned int nsecs )
{
	if ( signal(SIGALRM, sig_alrm) == SIG_ERR )
	      return (nsecs);
	if ( setjmp(env_alrm) == 0 ) {
		alarm(nsecs);
		pause();
	}
	return (alarm(0));
}

static void sig_int( int signo )
{
	int 		i, j;
	volatile int 	k;

	printf("\nsig_int starting\n");
	for ( i = 0; i < 300000; i++ )
	      for ( j = 0; j < 4000; j++ )
		    k += i * j;
	printf("sig_int finished\n");
}

int main( int argc, char *argv[] )
{
	unsigned int 	unslept;

	if ( signal(SIGINT, sig_int) == SIG_ERR )
	      err_sys("signal(SIGINT) error");
	unslept = sleep2(5);
	printf("sleep2 returned: %u\n", unslept);

	exit(0);
}
