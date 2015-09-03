/*
 * =====================================================================================
 *
 *       Filename:  cli_main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月22日 23时02分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "chatroom_cli.h"

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

char *getstr(char *buf, size_t size)
{
        int ch;
        int i = 0;

        while (((ch = getchar()) != '\n') && (i < size - 1))
                buf[i++] = ch;
        buf[i] = '\0';

        return buf;
}

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("Usage: ...\n");
                return 1;
        }

        const char *ip = argv[1];
        int port = atoi(argv[2]);

        struct sockaddr_in ser_addr;
        ser_addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &ser_addr.sin_addr);
        ser_addr.sin_port = htons(port);

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sockfd >= 0);

        int ret = connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
        assert(ret != -1);

        char ip_buf[16];
        printf("\nConnecting success, server ip: %s, port: %d\n\n",
                        inet_ntop(AF_INET, &ser_addr.sin_addr, ip_buf, 16),
                        ntohs(ser_addr.sin_port));

        /* 注册epoll内核事件表 */
        struct epoll_event events[MAX_EVENT_NUMBER];
        int epollfd = epoll_create(5);
        assert(epollfd != -1);
        addfd(epollfd, sockfd);
        addfd(epollfd, STDIN_FILENO);

        bool stop_client = false;

        while ( !stop_client )
        {
                int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
                int i;

                if ((number < 0) && (errno != EINTR))
                {
                        printf("epoll failure\n");
                        break;
                }

                for (i = 0; i < number; ++i)
                {
                        int fd = events[i].data.fd;

                        if ((fd == sockfd) && (events[i].events & EPOLLIN)) {
                                char recv_buf[BUFFER_SIZE];
                                memset(recv_buf, '\0', sizeof(recv_buf));
                                ret = recv(fd, recv_buf, BUFFER_SIZE, 0);
                                if (ret == -1) {
                                        continue;
                                } else if (ret == 0) {
                                        stop_client = true;
                                        break;
                                } else {
                                        printf("R: %s\n", recv_buf);
                                }
                        } else if ((fd == STDIN_FILENO) && (events[i].events & EPOLLIN)) {
                                char send_buf[BUFFER_SIZE];
                                memset(send_buf, '\0', sizeof(send_buf));
                                getstr(send_buf, BUFFER_SIZE);
                                if (strcmp(send_buf, "quit") == 0) {
                                        stop_client = true;
                                        break;
                                } else {
                                        //int ret;
                                        send(sockfd, send_buf, strlen(send_buf), 0);
                                        /*  
                                        if (ret <= 0) {
                                                printf("Send failure\n");
                                        } else {
                                                printf("Send success\n");
                                        } */
                                }
                        }
                }
        }
        printf("\nClient is quited!\n");

        close(sockfd);
        close(epollfd);

	return EXIT_SUCCESS;
}
