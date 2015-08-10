/*
 * =====================================================================================
 *
 *       Filename:  pro1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 22时56分04秒
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

int main(int argc, char *argv[], char **environ)
{
        int     i;

        printf("This is pro1\n");
        for (i = 0; environ[i] != NULL; i++)
                printf("%s\n", environ[i]);

	return EXIT_SUCCESS;
}
