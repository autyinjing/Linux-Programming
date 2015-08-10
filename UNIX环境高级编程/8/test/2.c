/*
 * =====================================================================================
 *
 *       Filename:  2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 17时42分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

static void 	f1(void), f2(void);

int main( int argc, char *argv[] )
{
	f1();
	f2();
	_exit(0);
}

static void f1( void )
{
	pid_t 	pid;

	if ( (pid = vfork()) < 0 )
	      err_sys("vfork error");
}

static void f2( void )
{
	char 	buf[1000];
	int 	i;

	for ( i = 0; i < sizeof(buf); i++ )
	      buf[i] = 0;
}
