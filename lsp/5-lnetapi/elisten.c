/*
 * =====================================================================================
 *
 *       Filename:  elisten.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 15时09分06秒
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

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("Usage: %s ip_addr port_num\n", argv[0]);
                return 1;
        }
        const char *ip = argv[1];
        int     port = atoi(argv[2]);

        struct sockaddr_in addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &addr.sin_addr);
        addr.sin_port = htons(port);

        int sock = socket(PF_INET, SOCK_STREAM, 0);
        assert(sock >= 0);

        int ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
        assert(ret != -1);

        ret = listen(sock, 5);
        assert(ret != -1);

        sleep(40);
        struct sockaddr_in client;
        socklen_t clilen = sizeof(client);
        
        int connfd = accept(sock, (struct sockaddr *)&client, &clilen);
        if (connfd < 0) {
                perror("accept: ");
        } else {
                /* 连接成功时打印客户端的IP地址和端口号 */
                char    remote[INET_ADDRSTRLEN];
                printf("connected with ip: %s and port: %d\n",
                                inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN), ntohs(client.sin_port));
                close(connfd);
        }

        close(sock);

	return EXIT_SUCCESS;
}

