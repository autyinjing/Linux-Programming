/*
 * =====================================================================================
 *
 *       Filename:  testinet_ntoa.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 13时13分44秒
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
        struct sockaddr_in     addr;
        addr.sin_addr = inet_addr("128.60.3.1");
	char    *szValue1 = inet_ntoa(addr.sin_addr);
        //char    *szValue2 = inet_ntoa(addr.sin_addr);

        printf("szValue1 = %s\n", szValue1);
        //printf("szValue2 = %s\n", szValue2);

	return EXIT_SUCCESS;
}
