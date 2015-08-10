/*
 * =====================================================================================
 *
 *       Filename:  bufser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 16时09分41秒
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define         BUFFER_SIZE     1024

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("...");
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);

        struct sockaddr_in serv;
        bzero(&serv, sizeof(serv));
        serv.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &serv.sin_addr);
        serv.sin_port = htons(port);

        int sock = socket(PF_INET, SOCK_STREAM, 0);
        assert(sock >= 0);
        int recvbuf = atoi(argv[3]);
        int len = sizeof(recvbuf);

        setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
        getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t *)&len);
        printf("the tcp recvive buffer size after setting is %d\n", recvbuf);

        //int ret = bind(sock, (struct sockaddr *)&serv);

	return EXIT_SUCCESS;
}
