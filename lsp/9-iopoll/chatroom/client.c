/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月27日 14时30分13秒
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

#include "../../nethead.h"
#include <poll.h>

#define BUFFER_SIZE     64

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("...\n");
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);

        struct sockaddr_in serv;
        bzero(&serv, sizeof(serv));
        serv.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &serv.sin_addr);
        serv.sin_port = htons(port);

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(sockfd >= 0);
        if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
        {
                printf("connection failed\n");
                close(sockfd);
                return 1;
        }

        struct pollfd fds[2];

        fds[0].fd = 0;
        fds[0].events = POLLIN;
        fds[0].revents = 0;
        fds[1].fd = sockfd;
        fds[1].events = POLLIN | POLLRDHUP;
        fds[1].revents = 0;

        //char read_buf[BUFFER_SIZE];
        int pipefd[2];
        int ret = pipe(pipefd);
        assert(ret != -1);

        while ( 1 )
        {
                ret = poll(fds, 2, -1);
                if (ret < 0)
                {
                        perror("poll: ");
                        break;
                }

                if (fds[1].revents & POLLRDHUP) {
                        printf("server close the connection.\n");
                        break;
                } else if (fds[1].revents & POLLIN) {
                        printf("server close the connection.\n");
                        break;
                }

                if (fds[0].revents & POLLIN)
                {
                        ret = splice(0, NULL, pipefd[1], NULL, 32768, 
                                        SPLICE_F_MORE | SPLICE_F_MOVE);
                        ret = splice(pipefd[0], NULL, sockfd, NULL, 32768,
                                        SPLICE_F_MORE | SPLICE_F_MOVE);
                }
        }

        close(sockfd);

	return EXIT_SUCCESS;
}
