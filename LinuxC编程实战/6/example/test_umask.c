/*
 * =====================================================================================
 *
 *       Filename:  test_umask.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月17日 12时45分15秒
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

int main( int argc, char *argv[] )
{
	umask(0);
	if ( creat("example_681.test", S_IRWXU | S_IRWXG | S_IRWXO) < 0 ) {
		perror("creat");
		exit(1);
	}

	umask(S_IRWXO);
	if ( creat("example_682.test", S_IRWXU | S_IRWXG | S_IRWXO) < 0 ) {
		perror("creat");
		exit(1);
	}

	return EXIT_SUCCESS;
}
