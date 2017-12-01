/*
 * =====================================================================================
 *
 *       Filename:  4-6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 23时09分59秒
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
#include <utime.h>

int main( int argc, char *argv[] )
{
	int 		i, fd;
	struct stat 	statbuf;
	struct utimbuf timebuf;

	for ( i = 1; i < argc; i++ ) {
		if ( stat(argv[i], &statbuf) < 0 ) {
		      err_ret( "%s: stat error", argv[1] );
		      continue;
		}
		if ( (fd = open(argv[i], O_RDWR | O_TRUNC)) < 0 ) {
			err_ret( "%s: open error", argv[i] );
			continue;
		}
		close(fd);
		timebuf.actime = statbuf.st_atime;
		timebuf.modtime = statbuf.st_mtime;
		if ( utime(argv[i], &timebuf) < 0 ) {
			err_ret( "%s: utime error", argv[i] );
			continue;
		}
	}

	exit(0);
}
