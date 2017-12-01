/*
 * =====================================================================================
 *
 *       Filename:  3-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月11日 21时03分39秒
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
	if ( lseek(STDIN_FILENO, 0, SEEK_CUR) == -1 )
	      printf( "cannot seek\n" );
	else
	      printf( "seek OK\n" );

	exit(0);
}

