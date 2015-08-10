/*
 * =====================================================================================
 *
 *       Filename:  my_rwl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月17日 08时53分38秒
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
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*自定义错误处理函数*/
void my_err( const char *err_string, int line )
{
	fprintf(stderr, "line:%d ", line );
	perror(err_string);
	exit(1);
}

int my_read( int fd )
{
	int 	len;
	int 	ret;
	int 	i;
	char 	read_buf[64];

	/*获取文件长度并保持文件读写指针在文件开始处*/
	if ( lseek(fd, 0, SEEK_END) == -1 ) {
		my_err("lseek", __LINE__);
	}
	if ( (len = lseek(fd, 0, SEEK_CUR)) == -1 ) {
		my_err("lseek", __LINE__);
	}
	if ( (lseek(fd, 0, SEEK_SET)) == -1 ) {
		my_err("lseek", __LINE__);
	}

	printf("len:%d\n", len);

	/*读数据*/
	if ( (ret = read(fd, read_buf, len)) < 0 ) {
		my_err("read", __LINE__);
	}

	/*打印数据*/
	for ( i = 0; i < len; ++i ) {
		printf("%c", read_buf[i]);
	}
	printf("\n");

	return ret;
}

int main( int argc, char *argv[] )
{
	int 	fd;
	char 	write_buf[32] = "hello world!";

	//if ( (fd = creat("example_63.c", S_IRWXU)) == -1 ) {
	if ( (fd = open("example_63.c", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1 ) {
		my_err("open", __LINE__);
	} else {
		printf("create file success\n");
	}

	/*写数据*/
	if ( write(fd, write_buf, strlen(write_buf)) != strlen(write_buf) ) {
		my_err("write", __LINE__);
	}
	my_read(fd);

	/*演示文件的间隔*/
	printf("/*------------------*/\n");
	if ( lseek(fd, 10, SEEK_END) == -1 ) {
		my_err("lseek", __LINE__);
	}
	if ( write(fd, write_buf, strlen(write_buf)) != strlen(write_buf) ) {
		my_err("write", __LINE__);
	}
	my_read(fd);

	close(fd);
	return EXIT_SUCCESS;
}
