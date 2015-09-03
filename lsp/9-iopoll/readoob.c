/*
 * =====================================================================================
 *
 *       Filename:  readoob.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月11日 10时51分26秒
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

        int ret = 0;
        struct sockaddr_in address;
        memset(&address, '\0', sizeof(address));
        address.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &address.sin_addr);
        address.sin_port = htons(port);

        int listenfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(listenfd >= 0);
        ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
        assert(ret != -1);
        ret = listen(listenfd, 5);
        assert(ret != -1);

        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        int connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_len);
        if (connfd < 0) {
                printf("error is: %d\n", errno);
                close(listenfd);
        } else {
                char    buf[16];
                printf("Accept a new connect, IP: %s, port: %d\n", 
                                inet_ntop(AF_INET, &cli_addr.sin_addr, buf, cli_len), ntohs(cli_addr.sin_port));
        }

        char buf[1024];
        fd_set read_fds;
        fd_set exception_fds;
        FD_ZERO(&read_fds);
        FD_ZERO(&exception_fds);

        while ( 1 )
        {
                memset(buf, '\0', sizeof(buf));
                FD_SET(connfd, &read_fds);
                FD_SET(connfd, &exception_fds);
                ret = select(connfd+1, &read_fds, NULL, &exception_fds, NULL);
                if (ret < 0)
                {
                        printf("selection failure\n");
                        break;
                }

                /* 对于可读事件，采用普通的recv函数读取数据 */
                if (FD_ISSET(connfd, &read_fds))
                {
                        ret = recv(connfd, buf, sizeof(buf) - 1, 0);
                        if (ret <= 0)
                        {
                                break;
                        }
                        printf("get %d bytes of normal date: %s\n", ret, buf);
                }

                /* 对于异常事件，采用带MSG_OOB标志的recv函数读取带外数据 */
                if (FD_ISSET(connfd, &exception_fds))
                {
                        ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
                        if (ret <= 0)
                        {
                                break;
                        }
                        printf("get %d bytes of oob date: %s\n", ret, buf);
                }
        }

        close(connfd);
        close(listenfd);

	return EXIT_SUCCESS;
}
