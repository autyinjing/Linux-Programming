/*
 * =====================================================================================
 *
 *       Filename:  endian.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月08日 12时43分37秒
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
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned short hosts = 0x1234;
        unsigned short nets;
        unsigned long hostl = 0x12345678;
        unsigned long netl;

        nets = htons(hosts);
        netl = htonl(hostl);

        printf("Host ordered short: %#x \n", hosts);
        printf("Network ordered short: %#x \n", nets);

        printf("Host ordered long: %#lx \n", hostl);
        printf("Network ordered long: %#lx \n", netl);

	return EXIT_SUCCESS;
}

