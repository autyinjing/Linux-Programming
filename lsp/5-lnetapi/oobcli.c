/*
 * =====================================================================================
 *
 *       Filename:  oobcli.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 15时31分21秒
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
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("Usage: %s ip port\n", argv[0]);
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);

        struct sockaddr_in serv;
        bzero(&serv, sizeof(serv));
        serv.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &serv.sin_addr);
        serv.sin_port = htons(port);

        int sockfd = socket(PF_INET, SOCK_STREAM, 0);
        assert(sockfd >= 0);
        if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
                printf("connection failed\n");
        } else {
                const char *oob = "abc";
                const char *nor = "123";
                send(sockfd, nor, strlen(nor), 0);
                send(sockfd, oob, strlen(oob), MSG_OOB);
                send(sockfd, nor, strlen(nor), 0);
        }
        close(sockfd);

	return EXIT_SUCCESS;
}
