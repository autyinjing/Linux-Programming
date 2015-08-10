/*
 * =====================================================================================
 *
 *       Filename:  10-2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月27日 16时34分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include <pwd.h>

static void my_alarm( int signo )
{
	struct passwd 	*rootptr;

	printf("in signal handler\n");
	if ( (rootptr = getpwnam("root")) == NULL )
	      err_sys("getpwnam(root) error");
	alarm(1);
}

int main( int argc, char *argv[] )
{
	struct passwd 	*ptr;

	signal(SIGALRM, my_alarm);
	alarm(1);
	for ( ; ; ) {
		if ( (ptr = getpwnam("sar")) == NULL )
		      err_sys("getpwnam error");
		if ( strcmp(ptr->pw_name, "sar") != 0 )
		      printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
	}

	exit(0);
}
