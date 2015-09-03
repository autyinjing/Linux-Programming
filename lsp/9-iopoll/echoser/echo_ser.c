/*
 * =====================================================================================
 *
 *       Filename:  echoer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月11日 21时06分25秒
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

#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE 512
#define UDP_BUFFER_SIZE 1024

int setnonblocking(int fd)
{
        int old_option = fcntl(fd, F_GETFL);
        int new_option = old_option | O_NONBLOCK;
        fcntl(fd, F_SETFL, new_option);
        return old_option;
}

void addfd(int epollfd, int fd)
{
        struct epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLIN | EPOLLET;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
        setnonblocking(fd);
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

        /* 创建TCP socket，并将其绑定到端口port上 */
        int listenfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(listenfd >= 0);

        ret = bind(listenfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
        assert(ret != -1);

        ret = listen(listenfd, 5);
        assert(ret != -1);

        /* 创建UDP socket，并将其绑定到端口port上 */
        memset(&ser_addr, '\0', sizeof(ser_addr));
        ser_addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &ser_addr.sin_addr);
        ser_addr.sin_port = htons(port);
        int udpfd = socket(AF_INET, SOCK_DGRAM, 0);
        assert(udpfd >= 0);

        ret = bind(udpfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
        assert(ret != -1);

        struct epoll_event events[MAX_EVENT_NUMBER];
        int epollfd = epoll_create(5);
        assert(epollfd != -1);

        /* 注册TCP socket和UDP socket上的可读事件 */
        addfd(epollfd, listenfd);
        addfd(epollfd, udpfd);

        while ( 1 )
        {
                int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
                if (number < 0)
                {
                        printf("epoll failure\n");
                        break;
                }

                int i;
                for (i = 0; i < number; i++)
                {
                        int sockfd = events[i].data.fd;
                        char ip_buf[16];
                        if (sockfd == listenfd) {
                                struct sockaddr_in cli_addr;
                                socklen_t cli_len = sizeof(cli_addr);
                                int connfd = accept(listenfd, 
                                                (struct sockaddr *)&cli_addr, &cli_len);
                                addfd(epollfd, connfd);
                                printf("Accept a new connection, IP: %s, Port: %d\n",
                                                inet_ntop(AF_INET, &cli_addr, ip_buf, 16),
                                                ntohs(cli_addr.sin_port));
                        } else if (sockfd == udpfd) {
                                char buf[UDP_BUFFER_SIZE];
                                memset(buf, '\0', UDP_BUFFER_SIZE);
                                struct sockaddr_in cli_addr;
                                socklen_t cli_len = sizeof(cli_addr);

                                ret = recvfrom(udpfd, buf, UDP_BUFFER_SIZE-1, 0,
                                                (struct sockaddr *)&cli_addr, &cli_len);
                                if (ret > 0)
                                {
                                        printf("Recvied a udp message: %s\n", buf);
                                        sendto(udpfd, buf, UDP_BUFFER_SIZE-1, 0,
                                                        (struct sockaddr *)&cli_addr, cli_len);
                                }
                        } else if (events[i].events & EPOLLIN) {
                                char buf[TCP_BUFFER_SIZE];
                                while ( 1 )
                                {
                                        memset(buf, '\0', TCP_BUFFER_SIZE);
                                        ret = recv(sockfd, buf, TCP_BUFFER_SIZE-1, 0);
                                        if (ret < 0) {
                                                if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                                                        break;
                                                close(sockfd);
                                                break;
                                        } else if (ret == 0) {
                                                printf("A client left!\n");
                                                close(sockfd);
                                        } else {
                                                printf("Recvied a tcp message: %s\n", buf);
                                                send(sockfd, buf, ret, 0);
                                        }
                                }
                        } else {
                                printf("Something else happened \n");
                        }
                }
        }

        close(listenfd);

	return EXIT_SUCCESS;
}
