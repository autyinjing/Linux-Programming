/*
 * =====================================================================================
 *
 *       Filename:  10-3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月27日 16时42分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include <sys/wait.h>

static void 	sig_cld( int );

int main( int argc, char *argv[] )
{
	pid_t 	pid;

	if ( signal(SIGCLD, sig_cld) == SIG_ERR )
	      perror("signal error");
	if ( (pid = fork()) < 0 ) {
		perror("fork error");
	} else if ( pid == 0 ) {
		sleep(2);
		_exit(0);
	}
	pause();

	exit(0);
}

static void sig_cld( int signo )
{
	pid_t 	pid;
	int 	status;

	printf("SIGCLD received\n");
	if ( (pid = wait(&status)) < 0 )
	      perror("wait error");
	if ( signal(SIGCLD, sig_cld) == SIG_ERR )
	      perror("signal error");
	printf("pid = %d\n", pid);
}
