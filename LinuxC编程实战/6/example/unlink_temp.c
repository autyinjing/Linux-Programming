/*
 * =====================================================================================
 *
 *       Filename:  unlink_temp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月19日 08时12分05秒
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

void my_err( const char *err_string, int line )
{
	fprintf(stderr, "line:%d", line);
	perror(err_string);
	exit(1);
}

int main( int argc, char *argv[] )
{
	int 	fd;
	char 	buf[32];

	if ( (fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0 ) {
		my_err("open", __LINE__);
	}

	if ( unlink("temp") < 0 ) {
		my_err("unlink", __LINE__);
	}
	printf("file unlinked\n");

	if ( write(fd, "temp", 5) < 0 ) {
		my_err("write", __LINE__);
	}
	if ( lseek(fd, 0, SEEK_SET) == -1 ) {
		my_err("lseek", __LINE__);
	}
	if ( read(fd, buf, 5) < 0 ) {
		my_err("read", __LINE__);
	}
	printf("%s\n", buf);

	return EXIT_SUCCESS;
}
