/*
 * =====================================================================================
 *
 *       Filename:  test_gdb.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 10时20分48秒
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

int get_sum( int n )
{
	int 	sum = 0, i;
	for ( i = 0; i < n; ++i )
	      sum += i;
	return sum;
}

int main( int argc, char *argv[] )
{
	int 	i = 100, result;

	result = get_sum(i);
	printf("sum = %d\n", result);

	return EXIT_SUCCESS;
}
