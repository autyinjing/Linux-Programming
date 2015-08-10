/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 12时19分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "head.h"

int main(int argc, char *argv[])
{
	int     listenfd;
        listenfd = socket_bind(IPADDRESS, PORT);
        listen(listenfd, LISTENQ);
        do_poll(listenfd);

	return EXIT_SUCCESS;
}

int socket_bind(const char *ip, int port)
{
        int     listenfd;
        struct sockaddr_in      servaddr;
        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        if (listenfd == -1)
        {
                perror("socket error: ");
                exit(1);
        }
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &servaddr.sin_addr);
        servaddr.sin_port = htons(port);
        if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
        {
                perror("bind error: ");
                exit(1);
        }
        return listenfd;
}

void do_poll(int listenfd)
{
        int     connfd;
        struct sockaddr_in      cliaddr;
        socklen_t       cliaddrlen;
        struct pollfd   clientfds[OPEN_MAX];
        int     maxi;
        int     i;
        int     nready;

        /* 添加监听描述符 */
        clientfds[0].fd = listenfd;
        clientfds[0].events = POLLIN;

        /* 初始化客户连接描述符 */
        for (i = 1; i < OPEN_MAX; i++)
                clientfds[i].fd = -1;
        maxi = 0;

        /* 循环处理 */
        for ( ; ; )
        {
                nready = poll(clientfds, maxi+1, INFTIM);
                if (nready == -1)
                {
                        perror("poll error: ");
                        exit(1);
                }

                /* 测试监听描述符是否就绪 */
                if (clientfds[0].revents & POLLIN)
                {
                        cliaddrlen = sizeof(cliaddr);
                        /* 接受新的连接 */
                        if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr,
                                                        &cliaddrlen)) == -1)
                        {
                                if (errno == EINTR) {
                                        continue;
                                } else {
                                        perror("accept error: ");
                                        exit(1);
                                }
                        }
                        fprintf(stdout, "accept a new client: %s:%d\n",
                                        inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
                        /* 将新的连接描述符添加到数组中 */
                        for (i = 1; i < OPEN_MAX; i++)
                        {
                                if (clientfds[i].fd < 0)
                                {
                                        clientfds[i].fd = connfd;
                                        break;
                                }
                        }
                        if (i == OPEN_MAX)
                        {
                                fprintf(stderr, "too many clients.\n");
                                exit(1);
                        }
                        /* 将新的描述符添加到读描述符集合中 */
                        clientfds[i].events = POLLIN;
                        /* 记录客户连接套接字的个数 */
                        maxi = (i > maxi ? i : maxi);
                        if (--nready <= 0)
                                continue;
                }
                /* 处理客户连接 */
                ser_handle_connection(clientfds, maxi);
        }
}

void ser_handle_connection(struct pollfd connfds[], int num)
{
        int     i, n;
        char    buf[MAXLINE];

        
        for (i = 1; i <= num; i++)
        {
                if (connfds[i].fd < 0)
                        continue;
                /* 测试客户描述符是否准备好 */
                if (connfds[i].revents & POLLIN)
                {
                        /* 接收客户端发送的消息 */
                        memset(buf, 0, MAXLINE);
                        n= read(connfds[i].fd, buf, MAXLINE);
                        if (n == 0)
                        {
                                close(connfds[i].fd);
                                connfds[i].fd = -1;
                                fprintf(stdout, "a client quit\n");
                                continue;
                        }
                        buf[strlen(buf)] = '\0';
                        fprintf(stdout, "%s", buf);
                        write(connfds[i].fd, buf, n);
                }
        }
}
