/*
 * =====================================================================================
 *
 *       Filename:  processimage.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 22时13分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), linuxeryinjing@gmail.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[], char **environ)
{
        int     i;

        printf("I am process image!\n");
        printf("My pid = %d, parentpid = %d\n", getpid(), getppid());
        printf("uid = %d, gid = %d\n", getuid(), getgid());

        for (i = 0; i < argc; i++)
                printf("argv[%d]:%s\n", i, argv[i]);

	return EXIT_SUCCESS;
}
