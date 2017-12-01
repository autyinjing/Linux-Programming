/*
 * =====================================================================================
 *
 *       Filename:  8-3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 20时10分28秒
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
	int 	status;

	if ( (pid = fork()) < 0 )
	      err_sys("fork error");
	else if ( pid == 0 )
	      exit(7);

	if ( wait(&status) != pid )
	      err_sys("wait error");
	pr_exit(status);

	if ( (pid = fork()) < 0 )
	      err_sys("fork error");
	else if ( pid == 0 )
	      abort();

	if ( wait(&status) != pid )
	      err_sys("wait error");
	pr_exit(status);

	if ( (pid = fork()) < 0 )
	      err_sys("fork error");
	else if ( pid == 0 )
	      status /= 0;

	if ( wait(&status) != pid )
	      err_sys("wait error");
	pr_exit(status);

	exit(0);
}
