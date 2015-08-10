/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 17时36分01秒
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

int main( int argc, char *argv[] )
{
	int 	var, i;
	char 	buf[MAXLINE];
	pid_t 	pid;

	var = 88;
	printf("before vfork\n");
	if ( (pid = vfork()) < 0 ) {
		err_sys("vfork error");
	} else if ( pid == 0 ) {
		glob++;
		var++;
		fclose(stdout);
		exit(0);
	}

	i = printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	sprintf(buf, "%d\n", i);
	write(STDOUT_FILENO, buf, strlen(buf));

	exit(0);
}
