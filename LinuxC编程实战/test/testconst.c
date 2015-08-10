/*
 * =====================================================================================
 *
 *       Filename:  testconst.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 22时23分26秒
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

int main(int argc, char *argv[])
{
        const int i = 3;
        *(int *)&i = 1;
        printf("%d\n", i);

	return EXIT_SUCCESS;
}
