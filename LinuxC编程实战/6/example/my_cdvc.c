/*
 * =====================================================================================
 *
 *       Filename:  my_cdvc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月19日 08时19分04秒
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
#include <linux/limits.h>
#include <unistd.h>

void my_err( const char *err_string, int line )
{
	fprintf(stderr, "line:%d ", line);
	perror(err_string);
	exit(1);
}

int main( int argc, char *argv[] )
{
	char 	buf[PATH_MAX + 1];

	if ( argc < 2 ) {
		printf("my_cd <target path>\n");
		exit(1);
	}

	if ( chdir(argv[1]) < 0 ) {
		my_err("chdir", __LINE__);
	}
	if ( getcwd(buf, 512) < 0 ) {
		my_err("getcwd", __LINE__);
	}
	printf("%s\n", buf);

	return EXIT_SUCCESS;
}
