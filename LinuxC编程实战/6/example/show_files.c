/*
 * =====================================================================================
 *
 *       Filename:  show_files.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月19日 08时26分17秒
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
#include <dirent.h>

int my_readir( const char *path )
{
	DIR 		*dir;
	struct dirent 	*ptr;

	if ( (dir = opendir(path)) == NULL ) {
		perror("opendir");
		return -1;
	}
	while ( (ptr = readdir(dir)) != NULL ) {
		printf("file name: %s\n", ptr->d_name);
	}
	closedir(dir);

	return 0;
}

int main( int argc, char *argv[] )
{
	if ( argc < 2 ) {
		printf("listfile <target path>\n");
		exit(1);
	}

	if ( my_readir(argv[1]) < 0 ) {
		exit(1);
	}

	return EXIT_SUCCESS;
}
