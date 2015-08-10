/*
 * =====================================================================================
 *
 *       Filename:  struct_size.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 11时35分21秒
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

struct tmp
{
	int a: 17;
};

int main( int argc, char *argv[] )
{
	printf("%lu\n", sizeof(struct tmp));

	return EXIT_SUCCESS;
}
