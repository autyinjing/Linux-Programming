/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 15时38分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "head.h"

/* 函数声明 */
/* 处理连接 */
static void handle_connection(int sockfd);

/* 处理事件 */
static void
handle_events(int epollfd, struct epoll_event events[], int num, int sockfd, char *buf);

/* 处理读事件 */
static void do_read(int epollfd, int fd, int sockfd, char *buf);

/* 处理写事件 */
static void do_write(int epollfd, int fd, int sockfd, char *buf);

/* 添加事件 */
static void add_event(int epollfd, int fd, int state);

/* 删除事件 */
static void delete_event(int epollfd, int fd, int state);

/* 修改事件 */
static void modify_event(int epollfd, int fd, int state);

int main(int argc, char *argv[])
{
	int     sockfd;
        struct sockaddr_in      servaddr;
        
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                perror("socket error: ");
                exit(1);
        }
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);
        servaddr.sin_port = htons(PORT);
        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
        {
                perror("connect error: ");
                exit(1);
        }
        handle_connection(sockfd);
        close(sockfd);

	return EXIT_SUCCESS;
}

static void handle_connection(int sockfd)
{
        int     epollfd;
        struct epoll_event      events[EPOLLEVENTS];
        char    buf[MAXSIZE];
        int     ret;

        epollfd = epoll_create(FDSIZE);
        add_event(epollfd, STDIN_FILENO, EPOLLIN);
        memset(buf, 0, sizeof(buf));
        for ( ; ; )
        {
                ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
                handle_events(epollfd, events, ret, sockfd, buf);
        }
        close(epollfd);
}

static void
handle_events(int epollfd, struct epoll_event events[], int num, int sockfd, char *buf)
{
        int     fd;
        int     i;
        
        for (i = 0; i < num; i++)
        {
                fd = events[i].data.fd;
                if (events[i].events & EPOLLIN)
                        do_read(epollfd, fd, sockfd, buf);
                else if (events[i].events & EPOLLOUT)
                        do_write(epollfd, fd, sockfd, buf);
        }
}

static void do_read(int epollfd, int fd, int sockfd, char *buf)
{
        int     nread;

        nread = read(fd, buf, MAXSIZE);
        if (nread == -1) {
                perror("read error: ");
                close(fd);
        } else if (nread == 0) {
                fprintf(stderr, "server close.\n");
                close(fd);
        } else {
                if (fd == STDIN_FILENO) {
                        add_event(epollfd, sockfd, EPOLLOUT);
                } else {
                        delete_event(epollfd, sockfd, EPOLLIN);
                        add_event(epollfd, STDOUT_FILENO, EPOLLOUT);
                }
        }
}

static void do_write(int epollfd, int fd, int sockfd, char *buf)
{
        int     nwrite;

        nwrite = write(fd, buf, strlen(buf));
        if (nwrite == -1) {
                perror("write error: ");
                close(fd);
        } else {
                if (fd == STDOUT_FILENO)
                        delete_event(epollfd, fd, EPOLLOUT);
                else
                        modify_event(epollfd, fd, EPOLLIN);
        }
        memset(buf, 0, MAXSIZE);
}

static void add_event(int epollfd, int fd, int state)
{
        struct epoll_event      ev;
        ev.events = state;
        ev.data.fd = fd;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state)
{
        struct epoll_event      ev;
        ev.events = state;
        ev.data.fd = fd;
        epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state)
{
        struct epoll_event      ev;
        ev.events = state;
        ev.data.fd = fd;
        epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}
