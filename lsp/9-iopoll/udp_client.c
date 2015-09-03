/*
 * =====================================================================================
 *
 *       Filename:  udp_client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月11日 21时41分38秒
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

#include "net.h"

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("...\n");
                return 1;
        }

        const char *ip = argv[1];
        int port = atoi(argv[2]);

        struct sockaddr_in ser_addr;
        ser_addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &ser_addr.sin_addr);
        ser_addr.sin_port = htons(port);

        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        assert(sockfd >= 0);

        while ( 1 )
        {
                char    input[1024];
                socklen_t ser_len = sizeof(ser_addr);
                memset(input, '\0', sizeof(input));
                scanf("%s", input);
                if (strcmp(input, "quit") == 0)
                        break;
                sendto(sockfd, input, strlen(input), 0, 
                                (struct sockaddr *)&ser_addr, sizeof(ser_addr));
                
                memset(input, '\0', sizeof(input));
                recvfrom(sockfd, input, 1023, 0,
                                (struct sockaddr *)&ser_addr, &ser_len);
                printf("%s\n", input);
        }

	return EXIT_SUCCESS;
}
