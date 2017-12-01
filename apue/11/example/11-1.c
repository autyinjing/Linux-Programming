/*
 * =====================================================================================
 *
 *       Filename:  11-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月04日 13时20分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include <pthread.h>

pthread_t 	ntid;

void printids( const char *s )
{
	pid_t 		pid;
	pthread_t 	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,\
				(unsigned int)tid, (unsigned int)tid);
}

void *thr_fn( void *arg )
{
	printids("new thread: ");
	return ((void *)0);
}

int main( int argc, char *argv[] )
{
	int 	err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if ( err != 0 )
	      err_quit("can't create thread: %s\n", strerror(err));
	printids("main thread: ");
	sleep(1);
	exit(0);
}
