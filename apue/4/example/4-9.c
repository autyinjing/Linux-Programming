/*
 * =====================================================================================
 *
 *       Filename:  4-9.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 23时20分53秒
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
	char 	*ptr;
	int 	size = 255;

	if ( chdir("/tmp") < 0 )
	      err_sys("chdir failed");

	ptr = (char *)malloc(size);
	if ( getcwd(ptr, size) == NULL )
	      err_sys("getcwd failed");

	printf( "cwd = %s\n", ptr );

	exit(0);
}
