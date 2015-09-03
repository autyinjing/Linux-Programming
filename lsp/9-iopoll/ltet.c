/*
 156gg* =====================================================================================
 *
 *       Filename:  ltet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月11日 14时02分52秒
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
#include <sys/epoll.h>
#include <stdbool.h>

#include "net.h"

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE     10

/* 将文件描述符设置为非阻塞的 */
int setnonblocking(int fd)
{
        int old_option = fcntl(fd, F_GETFL);
        int new_option = old_option | O_NONBLOCK;
        fcntl(fd, F_SETFL, new_option);
        
        return old_option;
}

/* 将文件描述符fd上的EPOLLIN注册到epollfd指示的epoll内核事件表中，参数enable_et指定是否对fd启用ET模式 */
void addfd(int epollfd, int fd, bool enable_et)
{
        struct epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLIN;
        if ( enable_et )
                event.events |= EPOLLET;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
        setnonblocking(fd);
}

/* LT模式的工作流程 */
void lt(struct epoll_event *events, int number, int epollfd, int listenfd)
{
        int i;
        char buf[BUFFER_SIZE];
        char ip[16];
        for (i = 0; i < number; i++)
        {
                int sockfd = events[i].data.fd;
                if (sockfd == listenfd) {
                        struct sockaddr_in cli_addr;
                        socklen_t cli_len = sizeof(cli_addr);
                        int connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_len);
                        addfd(epollfd, connfd, false);  /* 对connfd禁用ET模式 */
                        printf("Accept a new connect, IP: %s, port: %d\n",
                                        inet_ntop(AF_INET, &cli_addr.sin_addr, ip, 16),
                                        ntohs(cli_addr.sin_port));
                } else if (events[i].events & EPOLLIN) {
                        /* 只要socket的读缓存中还有未读出的数据，这段代码就被触发 */
                        printf("level trigger once\n");
                        memset(buf, '\0', BUFFER_SIZE);
                        int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
                        if (ret <= 0)
                        {
                                close(sockfd);
                                continue;
                        }
                        printf("Get %d bytes of content: %s\n", ret, buf);
                } else {
                        printf("Something else happened \n");
                }
        }
}

/* ET模式的工作流程 */
void et(struct epoll_event *events, int number, int epollfd, int listenfd)
{
        int i;
        char buf[BUFFER_SIZE];
        char ip[16];
        for (i = 0; i < number; i++)
        {
                int sockfd = events[i].data.fd;
                if (sockfd == listenfd) {
                        struct sockaddr_in cli_addr;
                        socklen_t cli_len = sizeof(cli_addr);
                        int connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_len);
                        addfd(epollfd, connfd, true);   /* 对connfd开启ET模式 */
                        printf("Accept a new connect, IP: %s, port: %d\n",
                                        inet_ntop(AF_INET, &cli_addr.sin_addr, ip, 16),
                                        ntohs(cli_addr.sin_port));
                } else if (events[i].events & EPOLLIN) {
                        /* 这段代码不会被重复触发，所以我们循环读取数据，以确保把socket读缓存中的所有数据读出 */
                        printf("event trigger once\n");
                        while ( 1 )
                        {
                                memset(buf, '\0', BUFFER_SIZE);
                                int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
                                if (ret < 0) {
                                        /* 对于非阻塞IO，下面的条件成立表示数据已经全部读取完毕，此后，epoll就能再次触发sockfd上的EPOLLIN事件，以驱动下一次读操作 */
                                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                                        {
                                                printf("read later\n");
                                                break;
                                        }
                                        close(sockfd);
                                        break;
                                } else if (ret == 0) {
                                        close(sockfd);
                                } else {
                                        printf("Get %d bytes of content: %s\n", ret, buf);
                                }
                        }
                } else {
                        printf("Something else happened \n");
                }
        }
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
        assert(ret != -1);

        ret = listen(listenfd, 5);
        assert(ret != -1);

        struct epoll_event events[MAX_EVENT_NUMBER];
        int epollfd = epoll_create(5);
        assert(epollfd != -1);
        addfd(epollfd, listenfd, true);

        while ( 1 )
        {
                int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
                if (ret < 0)
                {
                        printf("epoll failure\n");
                        break;
                }

                //lt(events, ret, epollfd, listenfd);     /* 使用LT模式 */
                et(events, ret, epollfd, listenfd);     /* 使用ET模式 */
        }
        close(listenfd);

	return EXIT_SUCCESS;
}
