/*
 * =====================================================================================
 *
 *       Filename:  fcntl_access.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月17日 11时41分12秒
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
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

/*自定义的错误处理函数*/
void my_err( const char *err_string, int line )
{
	fprintf(stderr, "line:%d ", line);
	perror(err_string);
	exit(1);
}

int main( int argc, char *argv[] )
{
	int 	ret;
	int 	access_mode;
	int 	fd;

	if ( (fd = open("example_64.c", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU)) == -1 ) {
		my_err("open", __LINE__);
	}

	/*设置文件的打开方式*/
	if ( (ret = fcntl(fd, F_SETFL, O_APPEND)) < 0 ) {
		my_err("fcntl", __LINE__);
	}

	/*获取文件的打开方式*/
	if ( (ret = fcntl(fd, F_GETFL, 0)) < 0 ) {
		my_err("fcntl", __LINE__);
	}
	access_mode = ret & O_ACCMODE;
	if ( access_mode == O_RDONLY ) {
		printf("read only");
	} else if ( access_mode == O_WRONLY ) {
		printf("write only");
	} else if ( access_mode == O_RDWR ) {
		printf("read + write");
	}

	if ( ret & O_APPEND ) {
		printf(" , append");
	}
	if ( ret & O_NONBLOCK ) {
		printf(" , nonblock");
	}
	if ( ret & O_SYNC ) {
		printf(" , sync");
	}
	printf("\n");

	return EXIT_SUCCESS;
}
