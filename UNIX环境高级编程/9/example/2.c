/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月27日 15时23分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

static void pr_ids( char *name )
{
	printf("%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d, tcsid = %d\n",\
				name, getpid(), getppid(), getpgrp(),\
				tcgetpgrp(STDIN_FILENO), tcgetsid(STDIN_FILENO));
	fflush(stdout);
}

int main( int argc, char *argv[] )
{
	pid_t 	pid;

	pr_ids("parent");
	if ( (pid = fork()) < 0 ) {
		err_sys("fork error");
	} else if ( pid > 0 ) {
		exit(0);
	} else if ( pid == 0 ) {
		sleep(2);
		pr_ids("child");
		exit(0);
	}
}
