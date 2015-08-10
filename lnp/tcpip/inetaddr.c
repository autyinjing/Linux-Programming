/*
 * =====================================================================================
 *
 *       Filename:  inetaddr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月08日 13时05分19秒
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
	char    *addr1 = "1.2.3.4";
        char    *addr2 = "192.168.1.1";

        in_addr_t       data;

        data = inet_addr(addr1);
        printf("%s -> %#x \n", addr1, data);

        data = inet_addr(addr2);
        printf("%s -> %#x \n", addr2, data);

	return EXIT_SUCCESS;
}

