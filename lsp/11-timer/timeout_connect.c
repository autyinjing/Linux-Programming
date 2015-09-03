/*
 * =====================================================================================
 *
 *       Filename:  timeout_connect.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月19日 10时54分42秒
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

#include "../nethead.h"

/* 超时连接函数 */
int timeout_connect(const char *ip, int port, int time)
{
        int ret;
        struct sockaddr_in ser_addr;
        memset(&ser_addr, '\0', sizeof(ser_addr));
        ser_addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &ser_addr.sin_addr);
        ser_addr.sin_port = htons(port);

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sockfd >= 0);

        /* 通过SO_RCVTIMEO和SO_SNDTIMEO设置socket的超时时间 */
        struct timeval timeout;
        timeout.tv_sec = time;
        timeout.tv_usec = 0;
        socklen_t len = sizeof(timeout);
        ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
        assert(ret != -1);

        ret = connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
        if (ret == -1)
        {
                /* 超时对应的错误号是EINPROGRESS，如果下面这个条件成立，我们可以处理定时任务了 */
                if (errno == EINPROGRESS)
                {
                        printf("Connecting timeout, process timeout logic \n");
                        return -1;
                }
                printf("Errno occur when connecting to server\n");
                return -1;
        }
        return sockfd;
}

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("Usage: errno\n");
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);

        int sockfd = timeout_connect(ip, port, 10);
        if (sockfd < 0)
        {
                printf("Connect failure!\n");
                return 1;
        }

	return EXIT_SUCCESS;
}
