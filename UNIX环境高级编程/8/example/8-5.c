/*
 * =====================================================================================
 *
 *       Filename:  8-5.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 20时46分43秒
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

	if ( (pid = fork()) < 0 ) {
		err_sys("fork error");
	} else if ( pid == 0 ) {
		if ( (pid = fork()) < 0 )
		      err_sys("fork error");
		else if ( pid > 0 )
		      exit(0);

		sleep(2);
		printf("second child, parent pid = %d\n", getppid());
		exit(0);
	}

	if ( (waitpid(pid, NULL, 0)) != pid )
	      err_sys("waitpid error");

	exit(0);
}
