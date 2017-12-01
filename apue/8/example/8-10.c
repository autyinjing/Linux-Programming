/*
 * =====================================================================================
 *
 *       Filename:  8-10.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 15时42分09秒
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

int main( int argc, char *argv[] )
{
	pid_t 	pid;

	if ( (pid = fork()) < 0 ) {
		err_sys("fork error");
	} else if ( pid == 0 ) {
		if ( execlp("test", "test", "myarg1", "MY ARG2", (char *)0) < 0 )
		      err_sys("execl error");
	}

	if ( waitpid(pid, NULL, 0) < 0 )
	      err_sys("waitpid error");

	exit(0);
}
