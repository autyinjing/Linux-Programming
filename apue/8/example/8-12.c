/*
 * =====================================================================================
 *
 *       Filename:  8-12.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 16时37分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

int my_system( const char *cmdstring )
{
	pid_t 	pid;
	int 	status;

	if ( cmdstring == NULL )
	      return (1);

	if ( (pid = fork()) < 0 ) {
		status = -1;
	} else if ( pid == 0 ) {
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(127);
	} else {
		while ( waitpid(pid, &status, 0) < 0 ) {
			if ( errno != EINTR ) {
				status = -1;
				break;
			}
		}
	}
	return (status);
}
