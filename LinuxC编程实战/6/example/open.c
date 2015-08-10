/*
 * =====================================================================================
 *
 *       Filename:  open.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月17日 08时38分34秒
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
	int 	fd;

	if ( (fd = creat("temp", 0744)) < 1 ) {
		printf("creat error!\n");
		exit(1);
	}
	printf("creat success!\n");
	close(fd);

	return EXIT_SUCCESS;
}
