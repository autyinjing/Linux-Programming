/*
 * =====================================================================================
 *
 *       Filename:  unifiedevent.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月18日 11时17分07秒
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

#include <signal.h>
#include <sys/epoll.h>
#include <stdbool.h>

#define MAX_EVENT_NUMBER 1024

static int pipefd[2];

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

/* 信号处理函数 */
void sig_handler(int sig)
{
        /* 保留原来的errno，在函数最后恢复，以保证函数的可重入性 */
        int save_errno = errno;
        int msg = sig;
        send(pipefd[1], (char *)&msg, 1, 0);    /* 将信号写入管道，以通知主循环 */
        errno = save_errno;
}

/* 设置信号的处理函数 */
void addsig(int sig)
{
        struct sigaction sa;
        memset(&sa, '\0', sizeof(struct sigaction));
        sa.sa_handler = sig_handler;
        sa.sa_flags |= SA_RESTART;
        sigfillset(&sa.sa_mask);
        assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char *argv[])
{
	struct epoll_event events[MAX_EVENT_NUMBER];
        int epollfd = epoll_create(5);
        assert(epollfd != -1);

        /* 使用socketpair创建管道，注册pipefd[0]上的可读事件 */
        int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, pipefd);
        assert(ret != -1);
        setnonblocking(pipefd[1]);
        addfd(epollfd, pipefd[0]);

        /* 设置一些信号处理函数 */
        addsig(SIGHUP);
        addsig(SIGCHLD);
        addsig(SIGTERM);
        addsig(SIGINT);
        bool stop_server = false;

        while ( !stop_server )
        {
                int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
                int i;
                if ((number < 0) && (errno != EINTR))
                {
                        printf("epoll failure\n");
                        break;
                }

                for (i = 0; i < number; i++)
                {
                        int sockfd = events[i].data.fd;
                        if ((sockfd == pipefd[0]) && (events[i].events & EPOLLIN))
                        {
                                char signals[1024];
                                ret = recv(pipefd[0], signals, sizeof(signals), 0);
                                if (ret == -1) {
                                        continue;
                                } else if (ret == 0) {
                                        continue;
                                } else {
                                        int j;
                                        for (j = 0; j < ret; ++j)
                                        {
                                                switch (signals[j])
                                                {
                                                        case SIGCHLD:
                                                                printf("Recvied a signal of SIGCHLD\n");
                                                                continue;
                                                        case SIGHUP:
                                                                printf("Recvied a signal of SIGHUP\n");
                                                                continue;
                                                        case SIGTERM:
                                                                printf("Recvied a signal of SIGTERM\n");
                                                                stop_server = true;
                                                        case SIGINT:
                                                                printf("Recvied a signal of SIGINT\n");
                                                                stop_server = true;
                                                }
                                        }
                                }
                        }
                }
        }
        printf("close fds\n");
        close(pipefd[1]);
        close(pipefd[0]);

	return EXIT_SUCCESS;
}
