/*
 * =====================================================================================
 *
 *       Filename:  border.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 12时49分35秒
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

int main(int argc, char *argv[])
{
        unsigned a = 0x01000000;
	char    *p = (char *)&a;
        int     i;

        for (i = 0; i < sizeof(unsigned); i++)
                printf("0x%02x\n", p[i]);

	return EXIT_SUCCESS;
}
