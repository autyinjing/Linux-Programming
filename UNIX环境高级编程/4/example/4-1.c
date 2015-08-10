/*
 * =====================================================================================
 *
 *       Filename:  4-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 22时40分56秒
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
	int 		i;
	struct stat 	buf;
	char 		*ptr;

	for ( i = 1; i < argc; i++ ) {
		printf( "%s: ", argv[i] );
		if ( lstat(argv[i], &buf) < 0 ) {
			err_ret( "lstat error" );
			continue;
		}
		if ( S_ISREG(buf.st_mode) )
		      ptr = "regular";
		else if ( S_ISDIR(buf.st_mode) )
		      ptr = "directory";
		else if ( S_ISCHR(buf.st_mode) )
		      ptr = "character special";
		else if ( S_ISBLK(buf.st_mode) )
		      ptr = "block special";
		else if ( S_ISFIFO(buf.st_mode) )
		      ptr = "fifo";
		else if ( S_ISLNK(buf.st_mode) )
		      ptr = "symbolic link";
		else if ( S_ISSOCK(buf.st_mode) )
		      ptr = "socket";
		else
		      ptr = "** unknown mode **";
		printf( "%s\n", ptr );
	}

	exit(0);
}
