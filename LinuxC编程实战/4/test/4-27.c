/*
 * =====================================================================================
 *
 *       Filename:  4-27.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 11时32分55秒
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
#include <string.h>

int main( int argc, char *argv[] )
{
	char 	a;
	char 	*str= &a;
	strcpy(str, "hello");
	printf("%s\n", str);

	return EXIT_SUCCESS;
}
