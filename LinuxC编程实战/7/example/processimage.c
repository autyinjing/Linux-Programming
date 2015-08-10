/*
 * =====================================================================================
 *
 *       Filename:  processimage.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月20日 12时18分06秒
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
#include <unistd.h>

int main( int argc, char *argv[] )
{
	int 	i;

	printf("i am process image!\n");
	printf("My pid = %d, parentpid = %d\n", getpid(), getppid());
	printf("uid = %u, gid = %u\n", getuid(), getgid());

	for ( i = 0; i < argc; ++i )
	      printf("argv[%d]:%s\n", i, argv[i]);

	return EXIT_SUCCESS;
}
