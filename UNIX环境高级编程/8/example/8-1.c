/*
 * =====================================================================================
 *
 *       Filename:  8-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 19时35分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

int 	glob = 6;
char 	buf[] = "a write to stdout\n";

int main( int argc, char *argv[] )
{
	int 	var;
	pid_t 	pid;

	var = 88;
	if ( write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1 )
	      err_sys("write error");
	printf("before fork\n");

	if ( (pid = fork()) < 0 ) {
		err_sys("fork error");
	} else if ( pid == 0 ) {
		glob++;
		var++;
	} else {
		sleep(2);
	}

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var );

	exit(0);
}
