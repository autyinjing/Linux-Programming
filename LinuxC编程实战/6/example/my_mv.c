/*
 * =====================================================================================
 *
 *       Filename:  my_mv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月17日 12时49分13秒
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
	if ( argc < 3 ) {
		perror("my_mv <old file> <new file>\n");
		exit(0);
	}

	if ( rename(argv[1], argv[2]) < 0 ) {
		perror("rename");
		exit(1);
	}

	return EXIT_SUCCESS;
}
