/*
 * =====================================================================================
 *
 *       Filename:  5-5.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 15时45分26秒
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
	if ( argc != 3 )
	      err_quit("usage: a.out <directory> <prefix>");

	printf("%s\n", tempnam(argv[1][0] != ' ' ? argv[1] : NULL, argv[2][0] != ' ' ? argv[2] : NULL));

	exit(0);
}
