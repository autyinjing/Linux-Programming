/*
 * =====================================================================================
 *
 *       Filename:  8-14.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 16时47分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include "8-12.c"

int main( int argc, char *argv[] )
{
	int 	status;

	if ( argc < 2 )
	      err_quit("command-line argument required");

	if ( (status = my_system(argv[1])) < 0 )
	      err_sys("my_system error");
	pr_exit(status);

	exit(0);
}
