/*
 * =====================================================================================
 *
 *       Filename:  oobser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 15时37分52秒
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
#include <errno.h>

#define         BUF_SIZE        1024

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

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        assert(sock >= 0);

        int ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
        assert(ret != -1);

        ret = listen(sock, 5);
        assert(ret != -1);

        struct sockaddr_in cli;
        socklen_t clilen = sizeof(cli);
        int connfd = accept(sock, (struct sockaddr *)&cli, &clilen);
        if (connfd < 0) {
                perror("accept: ");
        } else {
                char buffer[BUF_SIZE];

                memset(buffer, '\0', BUF_SIZE);
                ret = recv(connfd, buffer, BUF_SIZE-1, 0);
                printf("got %d bytes of normal data '%s'\n", ret, buffer);

                memset(buffer, '\0', BUF_SIZE);
                ret = recv(connfd, buffer, BUF_SIZE-1, MSG_OOB);
                printf("got %d bytes of oob data '%s'\n", ret, buffer);
                
                memset(buffer, '\0', BUF_SIZE);
                ret = recv(connfd, buffer, BUF_SIZE-1, 0);
                printf("got %d bytes of normal data '%s'\n", ret, buffer);

                close(connfd);
        }
        close(sock);

	return EXIT_SUCCESS;
}

