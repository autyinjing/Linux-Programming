/*
 * =====================================================================================
 *
 *       Filename:  4-8.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 23时19分17秒
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
	if ( chdir("/tmp") < 0 )
	      err_sys( "chdir failed" );
	printf( "chdir to /tmp successed\n" );

	exit(0);
}
