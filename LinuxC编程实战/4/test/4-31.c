/*
 * =====================================================================================
 *
 *       Filename:  4-31.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 11时43分45秒
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

#define MAX 	255

int main( int argc, char *argv[] )
{
	unsigned char 	a[MAX], i;

	for ( i = 0; i < MAX; ++i )
	      a[i] = i;

	for ( i = 0; i < MAX; ++i )
	      printf("%d ", a[i]);
	printf("\n");

	return EXIT_SUCCESS;
}
