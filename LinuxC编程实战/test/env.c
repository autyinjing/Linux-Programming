/*
 * =====================================================================================
 *
 *       Filename:  env.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 22时09分42秒
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
#include <malloc.h>

extern char     **environ;

int main(int argc, char *argv[])
{	
        int     i;

        printf("Argument:\n");
        for (i = 0; i < argc; i++)
                printf("argv[%d] is %s\n", i, argv[i]);
        printf("Environment:\n");
        for (i = 0; environ[i] != NULL; i++)
                printf("%s\n", environ[i]);

	return EXIT_SUCCESS;
}
