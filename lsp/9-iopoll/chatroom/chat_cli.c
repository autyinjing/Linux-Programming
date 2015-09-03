/*
 * =====================================================================================
 *
 *       Filename:  chat_cli.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月11日 16时18分42秒
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

#define BUFFER_SIZE 64

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("...\n");
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);

        struct sockaddr_in ser_addr;
        memset(&ser_addr, '\0', sizeof(ser_addr));
        ser_addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &ser_addr.sin_addr);
        ser_addr.sin_port = htons(port);

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sockfd >= 0);
        if (connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
        {
                printf("Connection failured\n");
                close(sockfd);
                return 1;
        }

        struct pollfd fds[2];
        /* 注册文件描述符0（标准输入）和文件描述符sockfd上的可读事件 */
        fds[0].fd = 0;
        fds[0].events = POLLIN;
        fds[0].revents = 0;
        fds[1].fd = sockfd;
        fds[1].events = POLLIN | POLLRDHUP;
        fds[1].revents = 0;

        char read_buf[BUFFER_SIZE];
        int pipefd[2];
        int ret = pipe(pipefd);
        assert(ret != -1);

        while ( 1 )
        {
                ret = poll(fds, 2, -1);
                if (ret < 0)
                {
                        printf("poll failure\n");
                        break;
                }
                
                if (fds[1].revents & POLLRDHUP) {
                        printf("Server close the connection\n");
                        break;
                } else if (fds[1].revents & POLLIN) {
                        memset(read_buf, '\0', BUFFER_SIZE);
                        recv(fds[1].fd, read_buf, BUFFER_SIZE-1, 0);
                        printf("%s\n", read_buf);
                }

                if (fds[0].revents & POLLIN)
                {
                        /* 使用splice将用户输入的数据直接写到sockfd上（零拷贝） */
                        ret = splice(0, NULL, pipefd[1], NULL, 32768, 
                                        SPLICE_F_MORE | SPLICE_F_MOVE);
                        ret = splice(pipefd[0], NULL, sockfd, NULL, 32768,
                                        SPLICE_F_MORE | SPLICE_F_MOVE);
                }
        }
        close(sockfd);

	return EXIT_SUCCESS;
}
