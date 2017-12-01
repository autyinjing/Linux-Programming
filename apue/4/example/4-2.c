/*
 * =====================================================================================
 *
 *       Filename:  4-2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 22时49分51秒
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
	if ( argc != 2 )
	      err_quit( "Usage: a.out <pathname>" );
	if ( access(argv[1], R_OK) < 0 )
	      err_ret( "access error for %s", argv[1] );
	else
	      printf( "read access OK\n" );
	if ( open(argv[1], O_RDONLY) < 0 )
	      err_ret( "open error for %s", argv[1] );
	else
	      printf( "open for reading OK\n" );

	exit(0);
}
