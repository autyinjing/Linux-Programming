/*
 * =====================================================================================
 *
 *       Filename:  10-8.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月27日 17时23分53秒
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

static void 	sig_alrm( int );
static jmp_buf 	env_alrm;

int main( int argc, char *argv[] )
{
	int 	n;
	char 	line[MAXLINE];

	if ( signal(SIGALRM, sig_alrm) == SIG_ERR )
	      err_sys("signal(SIGALRM) error");
	if ( setjmp(env_alrm) != 0 )
	      err_quit("read timeout");

	alarm(10);
	if ( (n = read(STDIN_FILENO, line, MAXLINE)) < 0 )
	      err_sys("read error");
	alarm(0);

	write(STDOUT_FILENO, line, n);

	exit(0);
}

static void sig_alrm( int signo )
{
	longjmp(env_alrm, 1);
}
