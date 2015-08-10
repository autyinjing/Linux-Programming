/*
 * =====================================================================================
 *
 *       Filename:  7-2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 16时28分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

static void 	my_exit1(void);
static void 	my_exit2(void);

int main( int argc, char *argv[] )
{ 
	if ( atexit(my_exit2) != 0 )
	      err_sys("can't register my_exit2");
	if ( atexit(my_exit1) != 0 )
	      err_sys("can't register my_exit1");
	if ( atexit(my_exit1) != 0 )
	      err_sys("can't register my_exit1");

	printf("main is done\n");

	return (0);
}

static void my_exit1(void)
{
	printf("first exit handler\n");
}

static void my_exit2(void)
{
	printf("second exit handler\n");
}
