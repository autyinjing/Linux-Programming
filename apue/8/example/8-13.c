/*
 * =====================================================================================
 *
 *       Filename:  8-13.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 16时42分57秒
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

	if ( (status = my_system("date")) < 0 )
	      err_sys("my_system error");
	pr_exit(status);

	if ( (status = my_system("nosuchcmd")) < 0 )
	      err_sys("my_system error");
	pr_exit(status);

	if ( (status = my_system("who; exit 44")) < 0 )
	      err_sys("my_system error");
	pr_exit(status);

	exit(0);
}
