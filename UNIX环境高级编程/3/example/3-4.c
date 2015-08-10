/*
 * =====================================================================================
 *
 *       Filename:  3-4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 11时53分46秒
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
	int 	val;

	if ( argc != 2 )
	      err_quit( "Usage: a.out <descriptor#>" );

	if ( (val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0 )
	      err_sys( "fcntl error for fd %d", atoi(argv[1]) );

	switch ( val & O_ACCMODE ) {
		case O_RDONLY:
			printf( "read only" );
			break;

		case O_WRONLY:
			printf( "write only" );
			break;

		case O_RDWR:
			printf( "read write" );
			break;

		default:
			err_dump( "unknow access mode" );
	}

	if ( val & O_APPEND )
	      printf( ", append" );
	if ( val & O_NONBLOCK )
	      printf( ", nonblocking" );

#if defined(O_SYNC)
	if ( val & O_SYNC )
	      printf( ", synchronous writes" );
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
	if ( val & O_FSYNC )
	      printf( ", synchronous writes" );
#endif
	putchar( '\n' );

	exit(0);
}
