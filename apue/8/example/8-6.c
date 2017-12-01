/*
 * =====================================================================================
 *
 *       Filename:  8-6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 21时25分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

static void 	charatatime( char * );

int main( int argc, char *argv[] )
{
	pid_t 	pid;

	if ( (pid = fork()) < 0 ) {
		err_sys("fork error");
	} else if ( pid == 0 ) {
		charatatime("output from child\n");
	} else {
		charatatime("output from child\n");
	}

	exit(0);
}

static void charatatime( char *str )
{
	char 	*ptr;
	int 	c;

	setbuf(stdout, NULL);
	for ( ptr = str; (c = *ptr++) != 0; )
	      putc(c, stdout);
}
