/*
 * =====================================================================================
 *
 *       Filename:  testread.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 16时39分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        char    buf[1024];
	int nread = read(STDIN_FILENO, buf, 1024);
        //scanf("%s", buf);
        //printf("%s", buf);
        write(STDOUT_FILENO, buf, nread - 1);

	return EXIT_SUCCESS;
}
