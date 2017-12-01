/*
 * =====================================================================================
 *
 *       Filename:  4-10.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 23时25分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include <sys/sysmacros.h>
#ifdef SOLARIS
#include <sys/mkdev.h>
#endif

int main( int argc, char *argv[] )
{
	int 		i;
	struct stat 	buf;

	for ( i = 1; i < argc; i++ ) {
		printf( "%s: ", argv[i] );
		if ( stat(argv[i], &buf) < 0 ) {
			err_ret("stat error");
			continue;
		}

		printf( "dev = %d/%d", major(buf.st_dev), minor(buf.st_dev) );
		if ( S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode) ) {
			printf( " (%s) rdev = %d/%d", \
						(S_ISCHR(buf.st_mode)) ? "character" : "block",\
						major(buf.st_rdev), minor(buf.st_rdev) );
		}
		printf( "\n" );
	}

	exit(0);
}
