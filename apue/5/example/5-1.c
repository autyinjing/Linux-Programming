/*
 * =====================================================================================
 *
 *       Filename:  5-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 15时19分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

int main( int argc, char *argv[] )
{
	int 	c;

	while ( (c = getc(stdin)) != EOF )
	      if ( putc(c, stdout) == EOF )
		    err_sys("output error");

	if ( ferror(stdin) )
	      err_sys("input error");

	exit(0);
}
