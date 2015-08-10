/*
 * =====================================================================================
 *
 *       Filename:  2-11.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 09时49分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
	int 	a, b, c, d;

	a = 10;
	b = a++;
	c = ++a;
	d = 10 * a++;

	printf("b, c, d: %d, %d, %d\n", b, c, d);

	return EXIT_SUCCESS;
}
