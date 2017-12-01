/*
 * =====================================================================================
 *
 *       Filename:  8-9.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 14时53分24秒
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
	char 		**ptr;
	extern char 	**environ;

	for ( i = 0; i < argc; i++ )
	      printf("argv[%d]: %s\n", i, argv[i]);

	for ( ptr = environ; *ptr != 0; ptr++ )
	      printf("%s\n", *ptr);

	exit(0);
}
