/*
 * =====================================================================================
 *
 *       Filename:  3-2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月11日 21时06分23秒
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

char 	buf1[] = "abcdefghij";
char 	buf2[] = "ABCDEFGHIJ";

int main( int argc, char *argv[] )
{
	int 	fd;

	if ( (fd = creat("file.hole", FILE_MODE)) < 0 )
	      err_sys( "creat error" );

	if ( write(fd, buf1, 10) != 10 )
	      err_sys( "buf1 write error" );

	if ( lseek(fd, 16384, SEEK_SET) == -1 )
	      err_sys( "lseek error" );

	if ( write(fd, buf2, 10) != 10 )
	      err_sys( "buf2 write error" );

	exit(0);
}

