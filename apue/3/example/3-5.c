/*
 * =====================================================================================
 *
 *       Filename:  3-5.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 12时06分01秒
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

void set_fl( int fd, int flag )
{
	int 	val;

	if ( (val = fcntl(fd, F_GETFL, 0)) < 0 )
	      err_sys( "fcntl F_GETFL error" );

	val |= flags;

	if ( fcntl(fd, F_SETFL, val) < 0 )
	      err_sys( "fcntl F_SETFL error" );
}

int main( int argc, char *argv[] )
{

	exit(0);
}
