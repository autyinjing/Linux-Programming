/*
 * =====================================================================================
 *
 *       Filename:  8-16.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 17时12分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

int main( int argc, char *argv[] )
{
	pid_t 	pid;

	if ( (pid = fork()) < 0 )
	      err_sys("fork error");
	else if ( pid != 0 ) {
		sleep(2);
		exit(2);
	}

	if ( (pid = fork()) < 0 )
	      err_sys("fork error");
	else if ( pid != 0 ) {
		sleep(4);
		abort();
	}

	if ( (pid = fork()) < 0 )
	      err_sys("fork error");
	else if ( pid != 0 ) {
		execl("/bin/dd", "dd", "if=/etc/termcap", "of=/dev/null", NULL);
		exit(7);
	}

	if ( (pid = fork()) < 0 )
	      err_sys("fork error");
	else if ( pid != 0 ) {
		sleep(8);
		exit(0);
	}

	sleep(6);
	kill(getpid(), SIGKILL);
	exit(6);
}
