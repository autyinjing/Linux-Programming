/*
 * =====================================================================================
 *
 *       Filename:  testlog.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月09日 13时38分30秒
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
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        
        if (fd < 0) {
                printf("Open \'%s\' falid!\n", argv[1]);
        } else {
                while ( 1 )
                {
                        char    str[20];
                        scanf("%s", str);
                        if (strcmp(str, "quit") == 0)
                                break;
                        strcat(str, "\n");
                        write(fd, str, strlen(str));
                }
                close(fd);
        }

	return EXIT_SUCCESS;
}
