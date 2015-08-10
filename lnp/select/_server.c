/*
 * =====================================================================================
 *
 *       Filename:  _server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 10时36分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), linuxeryinjing@gmail.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "_head.h"

int main(int argc, char *argv[])
{
	int     listenfd;
        listenfd = socket_bind(IPADDRESS, PORT);
        listen(listenfd, LISTENQ);
        do_select(listenfd);

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

void do_select(int listenfd)
{
        int     connfd;
        struct sockaddr_in      cliaddr;
        socklen_t        cliaddrlen;
        fd_set  rset, allset;
        int     maxfd, maxi;
        int     i;
        int     clientfds[FD_SETSIZE];
        int     nready;

        /* 初始化描述符集合 */
        for (i = 0; i < FD_SETSIZE; i++)
                clientfds[i] = -1;
        maxi = -1;
        FD_ZERO(&allset);
        /* 添加监听描述符 */
        FD_SET(listenfd, &allset);
        maxfd = listenfd;

        /* 监听并处理连接 */
        for ( ; ; )
        {
                rset = allset;

                /* 获取可用的描述符数 */
                nready = select(maxfd+1, &rset, NULL, NULL, NULL);
                if (nready == -1)
                {
                        perror("select error: ");
                        exit(1);
                }
                /* 测试监听描述符是否就绪 */
                if (FD_ISSET(listenfd, &rset))
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
                        /* 将新的连接描述符添加到集合中 */
                        for (i = 0; i < FD_SETSIZE; i++)
                        {
                                if (clientfds[i] < 0)
                                {
                                        clientfds[i] = connfd;
                                        break;
                                }
                        }
                        if (i == FD_SETSIZE)
                        {
                                fprintf(stderr, "too many clients.\n");
                                exit(1);
                        }
                        /* 将新的描述符添加到读描述符的集合中 */
                        FD_SET(connfd, &allset);
                        /* 获取描述符个数 */
                        maxfd = (connfd > maxfd ? connfd : maxfd);
                        /* 记录客户端连接套接字的个数 */
                        maxi = (i > maxi ? i : maxi);
                        if (--nready <= 0)
                                continue;
                }
                /* 处理客户连接 */
                ser_handle_connection(clientfds, maxi, &rset, &allset);
        }
}

void ser_handle_connection(int connfds[], int num, fd_set *prset, fd_set *pallset)
{
        int     i, n;
        char    buf[MAXLINE];
        
        memset(buf, 0, MAXLINE);
        for (i = 0; i <= num; i++)
        {
                if (connfds[i] < 0)
                        continue;
                /* 测试客户描述符是否准备就绪 */
                if (FD_ISSET(connfds[i], prset))
                {
                        /* 接收客户端发来的消息 */
                        memset(buf, 0, sizeof(buf));
                        n = read(connfds[i], buf, MAXLINE);
                        if (n == 0)
                        {
                                close(connfds[i]);
                                FD_CLR(connfds[i], pallset);
                                connfds[i] = -1;
                                fprintf(stdout, "a client quit\n");
                                continue;
                        }
                        buf[strlen(buf)] = '\0';
                        fprintf(stdout, "read msg is: %s", buf);
                        /* 向客户端发送buf */
                        write(connfds[i], buf, n);
                }
        }
}
