/*
 * =====================================================================================
 *
 *       Filename:  2-12.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 09时50分52秒
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

void exchange( int *a, int *b )
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void _exchange( int *a, int *b )
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

int main( int argc, char *argv[] )
{
	int 	a = 1, b = 2;

	printf("a, b: %d, %d\n", a, b);
	_exchange(&a, &b);
	printf("a, b: %d, %d\n", a, b);

	return EXIT_SUCCESS;
}
