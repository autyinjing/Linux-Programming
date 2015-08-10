/*
 * =====================================================================================
 *
 *       Filename:  err.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月10日 11时55分03秒
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
	fprintf( stderr, "EACCES: %s\n", strerror(EACCES) );
	errno = ENOENT;
	perror( argv[0] );
	exit(0);
}
