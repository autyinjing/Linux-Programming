/*
 * =====================================================================================
 *
 *       Filename:  inetntoa.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月08日 13时08分35秒
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
#include <string.h>

int main(int argc, char *argv[])
{
	struct in_addr addr1, addr2;
        char *str1, *str2;
        char buf[20];

        addr1.s_addr = htonl(0x01020304);
        addr2.s_addr = htonl(0xc0a80101);

        str1 = inet_ntoa(addr1);
        //printf("str1 is %s\n", str1);
        memset(buf, 0, sizeof(buf));
        memcpy(buf, str1, strlen(str1)+1);
        str2 = inet_ntoa(addr2);

        printf("%#x -> %s \n", addr1.s_addr, buf);
        printf("%#x -> %s \n", addr2.s_addr, str2);
        printf("buf = %p\n", buf);
        printf("str1 = %p\n", str1);
        printf("str2 = %p\n", str2);

	return EXIT_SUCCESS;
}
