/*
 * =====================================================================================
 *
 *       Filename:  5-4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 15时39分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"

int main( int argc, char *argv[] )
{
	char 	name[L_tmpnam], line[MAXLINE];
	FILE 	*fp;


	printf("%s\n", tmpnam(NULL));
	tmpnam(name);
	printf("%s\n", name);

	if ( (fp = tmpfile()) == NULL )
	      err_sys("tmpfile error");
	fputs("one line of output\n", fp);
	rewind(fp);
	if ( fgets(line, sizeof(line), fp) == NULL )
	      err_sys("fgets error");
	fputs(line, stdout);

	exit(0);
}
