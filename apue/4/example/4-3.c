/*
 * =====================================================================================
 *
 *       Filename:  4-3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月12日 22时55分14秒
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

#define RWRWRW 	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main( int argc, char *argv[] )
{
	umask(0);
	if ( creat("foo", RWRWRW ) < 0 )
	      err_sys( "creat error for foo" );
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if ( creat("bar", RWRWRW) < 0 )
	      err_sys( "creat error for bar" );

	exit(0);
}
