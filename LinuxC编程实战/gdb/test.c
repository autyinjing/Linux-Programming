/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 19时42分54秒
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

int get_sum(int n)
{
        int     sum = 0, i;
        for (i = 0; i < 100; i++)
                sum += i;
        return sum;
}

int main(int argc, char *argv[])
{
        int     i = 100, result;
        result = get_sum(i);
        printf("1+2+...+%d=%d\n", i, result);

	return EXIT_SUCCESS;
}
