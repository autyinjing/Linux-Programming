/*
 * =====================================================================================
 *
 *       Filename:  env.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月19日 12时50分38秒
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
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <malloc.h>

extern char 	**environ;

int main( int argc, char *argv[] )
{
	int 	i;

	printf("Argument:\n");
	for ( i = 0; i < argc; ++i ) {
		printf("argv[%d] is %s\n", i, argv[i]);
	}

	printf("Environment:\n");
	for ( i = 0; environ[i] != NULL; ++i )
	      printf("%s\n", environ[i]);

	return EXIT_SUCCESS;
}
