/*
 * =====================================================================================
 *
 *       Filename:  13-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月04日 15时10分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void daemonize( const char *cmd )
{
	int 			i, fd0, fd1, fd2;
	pid_t 			pid;
	struct rlimit 		rl;
	struct sigaction 	sa;

	umask(0);

	if ( getrlimit(RLIMIT_NOFILE, &rl) < 0 )
	      err_quit("%s: can't get file limit", cmd);

	if ( (pid = fork()) < 0 )
	      err_quit("%s: can't fork", cmd);
	else if ( pid != 0 )
	      exit(0);
	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if ( sigaction(SIGHUP, &sa, NULL) < 0 )
	      err_quit("%s: can't ignore SIGHUP");
	if ( (pid = fork()) < 0 )
	      err_quit("%s: can't fork", cmd);
	else if ( pid != 0 )
	      exit(0);

	if ( chdir("/") < 0 )
	      err_quit("%s: can't change directory to /");

	if ( rl.rlim_max == RLIM_INFINITY )
	      rl.rlim_max = 1024;
	for ( i = 0; i < rl.rlim_max; i++ )
	      close(i);

	fd0 = open("dev/null", O_RDWR);
	fd1 = dup(fd0);
	fd2 = dup(fd0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if ( fd0 != 0 || fd1 != 1 || fd2 != 2 ) {
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
}

int main( int argc, char *argv[] )
{
	daemonize(*argv);
}
