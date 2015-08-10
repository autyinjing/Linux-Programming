/*
 * =====================================================================================
 *
 *       Filename:  6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 17时50分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

#ifdef 	SOLARIS
#define PSCMD 	"ps -a -o pid,ppid,s,tty,comm"
#else
#define PSCMD 	"ps -o pid,ppid,state,tty,command"
#endif

int main( int argc, char *argv[] )
{
	pid_t 	pid;

	if ( (pid = fork()) < 0 )
	      err_sys("fork error");
	else if ( pid == 0 )
	      exit(0);

	sleep(4);
	system(PSCMD);

	exit(0);
}
