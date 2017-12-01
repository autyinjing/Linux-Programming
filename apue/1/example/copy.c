/*
 * =====================================================================================
 *
 *       Filename:  copy.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月10日 11时35分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */

#include "../../apue.h"

#define BUFFSIZE 	4096

int main( int argc, char *argv[] )
{
	int 	n;
	char 	buf[BUFFSIZE];

	while ( (n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0 )
	      if ( write(STDOUT_FILENO, buf, n) != n )
		    err_sys( "write error" );
	if ( n < 0 )
	      err_sys( "read error" );

	exit(0);
}
