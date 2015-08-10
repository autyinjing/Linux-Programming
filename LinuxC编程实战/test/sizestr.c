/*
 * =====================================================================================
 *
 *       Filename:  sizestr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 20时11分13秒
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

struct inner
{
        char    c1;
        double  d;
        char    c2;
};

union data4
{
        struct inner    t1;
        int     i;
        char    c;
};

struct data
{
        int     a;
        long    b;
        double  c;
        float   d;
        char    e[3];
        short   f;
}d;

union empty
{
        ;
};

struct data5
{
        ;
};

int main(int argc, char *argv[])
{
        printf("%lu\n", sizeof(struct data5));

	return EXIT_SUCCESS;
}
