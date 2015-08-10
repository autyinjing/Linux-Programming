/*
 * =====================================================================================
 *
 *       Filename:  5-3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 15时24分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

void pr_stdio( const char *, FILE * );

int main( int argc, char *argv[] )
{
	FILE 	*fp;
	
	fputs("enter any character\n", stdout);
	if ( getchar() == EOF )
	      err_sys("getchar error");
	fputs("one line to standard error\n", stderr);

	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if ( (fp = fopen("/etc/motd", "r")) == NULL )
	      err_sys("fopen error");
	if ( getc(fp) == EOF )
	      err_sys("getc error");
	pr_stdio("/etc/motd", fp);
	
	exit(0);
}

void pr_stdio( const char *name, FILE *fp )
{
	printf( "stream = %s, ", name );

	if ( fp->_IO_file_flags & _IO_UNBUFFERED )
	      printf("unbuffered");
	else if ( fp->_IO_file_flags & _IO_LINE_BUF )
	      printf("line buffered");
	else
	      printf("fully buffered");
	printf(", buffer size = %ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
}
