/*
 * =====================================================================================
 *
 *       Filename:  4-26.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 11时30分53秒
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
	int 	a[5] = { 1, 2, 3, 4, 5 };
	int 	*ptr = (int *)(&a + 1);
	printf("%d, %d\n", *(a+1), *(ptr-1));

	return EXIT_SUCCESS;
}
