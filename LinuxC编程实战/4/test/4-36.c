/*
 * =====================================================================================
 *
 *       Filename:  4-36.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 12时17分18秒
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

int fun( int a[], int n )
{
	if ( n == 1 )
	      return 1;
	if ( n == 2 )
	      return (a[n-1] >= a[n-2]);
	return ((a[n-1] >= a[n-2]) && fun(a, n-1));
}

int main( int argc, char *argv[] )
{
	int 	a[] = { 1, 2, 3, 4, 5, 6 };
	int 	b[] = { 1, 2, 3, 4, 5, 7, 6 };
	
	if ( fun(a, sizeof(a)/sizeof(a[0])) == 1 )
	      printf("a:OK\n");
	else
	      printf("b:NO\n");
	
	if ( fun(b, sizeof(b)/sizeof(b[0])) == 1 )
	      printf("a:OK\n");
	else
	      printf("b:NO\n");

	return EXIT_SUCCESS;
}
