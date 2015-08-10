/*
 * =====================================================================================
 *
 *       Filename:  7-3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 16时33分22秒
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
	int 	i;

	for ( i = 0; i < argc; i++ )
	      printf("argv[%d]: %s\n", i, argv[i]);

	exit(0);
}
