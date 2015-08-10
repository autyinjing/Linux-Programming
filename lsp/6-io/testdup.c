/*
 * =====================================================================================
 *
 *       Filename:  testdup.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月07日 15时24分13秒
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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int     fd = open("temp.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);

//        close(STDOUT_FILENO);
//        dup(fd);
//        printf("hello!");
//        close(fd);
        
//        close(STDOUT_FILENO);
        int ret = dup(fd);
        printf("%d      %d\n", fd, ret);

	return EXIT_SUCCESS;
}

