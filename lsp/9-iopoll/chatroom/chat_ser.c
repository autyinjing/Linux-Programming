/*
 * =====================================================================================
 *
 *       Filename:  chat_ser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月11日 16时54分18秒
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

#include "../net.h"

#include <poll.h>

#define USER_LIMIT 5    /* 最大用户数量 */
#define BUFFER_SIZE 64  /* 读缓冲区的大小 */
#define FD_LIMIT 65535  /* 文件描述符的数量限制 */

/* 客户数据的数据结构 */
struct client_data
{
        struct sockaddr_in address;     /* 用户的地址信息 */
        char *write_buf;                /* 其他用户发来的消息地址 */
        char buf[BUFFER_SIZE];          /* 写入缓冲区 */
};

int setnonblocking(int fd)
{
        int old_option = fcntl(fd, F_GETFL);
        int new_option = old_option | O_NONBLOCK;
        fcntl(fd, F_SETFL, new_option);
        return old_option;
}

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
        struct sockaddr_in ser_addr;
        memset(&ser_addr, '\0', sizeof(ser_addr));
        ser_addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &ser_addr.sin_addr);
        ser_addr.sin_port = htons(port);

        int listenfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(listenfd >= 0);

        ret = bind(listenfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
        assert(listenfd != -1);

        ret = listen(listenfd, 5);
        assert(ret != -1);

        /* 创建users数组，分配FD_LIMIT个对象，每个连接都可以获得一个对象，使用socket的值作为数组索引 */
        struct client_data *users = (struct client_data *)malloc(sizeof(struct client_data) * FD_LIMIT);
        assert(users != NULL);

        /* 限制用户数量来提高性能 */
        struct pollfd fds[USER_LIMIT+1];
        int user_counter = 0;
        int i;
        for (i = 1; i <= USER_LIMIT; ++i)
        {
                fds[i].fd = -1;
                fds[i].events = 0;
        }
        fds[0].fd = listenfd;
        fds[0].events = POLLIN | POLLERR;
        fds[0].revents = 0;

        while ( 1 )
        {
                ret = poll(fds, user_counter+1, -1);
                if (ret < 0)
                {
                        printf("poll failure\n");
                        break;
                }

                for (i = 0; i < user_counter+1; ++i)
                {
                        if ((fds[i].fd == listenfd) && (fds[i].revents & POLLIN)) {
                                struct sockaddr_in cli_addr;
                                socklen_t cli_len = sizeof(cli_addr);
                                int connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_len);
                                if (connfd < 0) {
                                        printf("errno is: %d\n", errno);
                                        continue;
                                } else {
                                        char ip[16];
                                        printf("Accept a new connection, IP: %s, Port: %d\n", 
                                                        inet_ntop(AF_INET, &cli_addr.sin_addr, ip, 16),
                                                        ntohs(cli_addr.sin_port));
                                }

                                /* 如果请求太多，则关闭新到的连接 */
                                if (user_counter >= USER_LIMIT)
                                {
                                        const char *info = "too many users\n";
                                        printf("%s\n", info);
                                        send(connfd, info, strlen(info), 0);
                                        close(connfd);
                                        continue;
                                }

                                /* 对于新的连接，同时修改fds和users数组，用socket来索引客户数据 */
                                user_counter++;
                                users[connfd].address = cli_addr;
                                setnonblocking(connfd);
                                fds[user_counter].fd = connfd;
                                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
                                fds[user_counter].revents = 0;
                                printf("Comes a new user, now have %d users\n", user_counter);
                        } else if (fds[i].revents & POLLERR) {
                                printf("Get an error from %d\n", fds[i].fd);
                                char errors[100];
                                memset(errors, '\0', 100);
                                socklen_t length = sizeof(errors);
                                if (getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR,
                                                        &errors, &length) < 0)
                                {
                                        printf("Get socket option failed\n");
                                }
                                continue;
                        } else if (fds[i].revents & POLLRDHUP) {
                                /* 如果客户端关闭连接，则服务器也关闭对应的连接，并将总用户数减1 */
                                users[fds[i].fd] = users[fds[user_counter].fd];
                                close(fds[i].fd);
                                fds[i] = fds[user_counter];
                                i--;
                                user_counter--;
                                printf("A client left, now have %d users\n", user_counter);
                        } else if (fds[i].revents & POLLIN) {
                                int connfd = fds[i].fd;
                                memset(users[connfd].buf, '\0', BUFFER_SIZE);
                                ret = recv(connfd, users[connfd].buf, BUFFER_SIZE, 0);
                                users[connfd].buf[strlen(users[connfd].buf) - 1] = '\0';        /* 去除换行符 */
                                printf("Get %d bytes of client data \'%s\' from %d\n", 
                                                ret, users[connfd].buf, connfd);
                                if (ret < 0) {
                                        /* 如果读操作出错，则关闭连接 */
                                        if (errno != EAGAIN)
                                        {
                                                close(connfd);
                                                users[fds[i].fd] = users[fds[user_counter].fd];
                                                fds[i] = fds[user_counter];
                                                i--;
                                                user_counter--;
                                        }
                                } else if (ret == 0) {
                                        ;
                                } else {
                                        /* 如果接收到客户数据，则通知其他socket连接准备写数据 */
                                        int j;
                                        for (j = 1; j <= user_counter; ++j)
                                        {
                                                if (fds[j].fd == connfd)
                                                        continue;
                                                fds[j].events |= ~POLLIN;
                                                fds[j].events |= POLLOUT;
                                                users[fds[j].fd].write_buf = users[connfd].buf;
                                        }
                                }
                        } else if (fds[i].revents & POLLOUT) {
                                int connfd = fds[i].fd;
                                if ( !users[connfd].write_buf )
                                        continue;
                                ret = send(connfd, users[connfd].write_buf, 
                                                strlen(users[connfd].write_buf), 0);
                                users[connfd].write_buf = NULL;
                                /* 写完数据后需要重新注册fds[i]上的可读事件 */
                                fds[i].events |= ~POLLOUT;
                                fds[i].events |= POLLIN;
                        }
                }
        }

        free(users);

	return EXIT_SUCCESS;
}
