/*
 * =====================================================================================
 *
 *       Filename:  byteorder.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 12时46分10秒
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
	union
        {
                short   value;
                char union_bytes[sizeof(short)];
        } test;
        test.value = 0x0102;
        if ((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2)) {
                printf("Big endian\n");
        } else if ((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1)) {
                printf("Little endian\n");
        } else {
                printf("Unknown...\n");
        }

	return EXIT_SUCCESS;
}
