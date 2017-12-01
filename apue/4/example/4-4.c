/*
 * =====================================================================================
 *
 *       Filename:  4-4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 22时59分15秒
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
	struct stat 	statbuf;

	if ( stat("foo", &statbuf) < 0 )
	      err_sys( "stat error for foo" );
	if ( chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0 )
	      err_sys( "chmod error for foo" );
	if ( chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0 )
	      err_sys( "chmod error for bar" );

	exit(0);
}
