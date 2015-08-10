/*
 * =====================================================================================
 *
 *       Filename:  4-5.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 23时03分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include <fcntl.h>

int main( int argc, char *argv[] )
{
	if ( open("tempfile", O_RDWR) < 0 )
	      err_sys( "open error" );
	if ( unlink("tempfile") < 0 )
	      err_sys( "unlink error" );
	printf( "file unlinked\n" );
	sleep(15);
	printf( "done\n" );

	exit(0);
}
