/*
 * =====================================================================================
 *
 *       Filename:  8-8.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 14时45分18秒
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

char 	*env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main( int argc, char *argv[] )
{
	pid_t 	pid;

	if ( (pid = fork()) < 0 ) {
		err_sys("fork error");
	} else if ( pid == 0 ) {
		if ( execle("/home/yinjing/echoall", "echoall", "myarg1",\
						"MY ARG2", (char *)0, env_init) < 0 )
		      err_sys("execle error");
	}
	if ( waitpid(pid, NULL, 0) < 0 )
	      err_sys("wait error");

	if ( (pid = fork()) < 0 ) {
		err_sys("fork error");
	} else if ( pid == 0 ) {
		if ( execlp("./echoall", "echoall", "only 1 arg", (char *)0) < 0 )
		      err_sys("execlp error");
	}

	exit(0);
}
