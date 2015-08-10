/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 12时44分11秒
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
	int     sockfd;
        struct sockaddr_in      servaddr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1)
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
        printf("connect success!\n");
        /* 处理连接描述符 */
        cli_handle_connection(sockfd);

	return EXIT_SUCCESS;
}

void cli_handle_connection(int sockfd)
{
        char    sendline[MAXLINE], recvline[MAXLINE];
        struct pollfd   pfds[2];
        int     n;

        /* 添加连接描述符 */
        pfds[0].fd = sockfd;
        pfds[0].events = POLLIN;
        /* 添加标准输入描述符 */
        pfds[1].fd = STDIN_FILENO;
        pfds[1].events = POLLIN;
        for ( ; ; )
        {
                poll(pfds, 2, -1);
                if (pfds[0].revents & POLLIN)
                {
                        memset(recvline, 0, sizeof(recvline));
                        n = read(sockfd, recvline, MAXLINE);
                        if (n == 0)
                        {
                                fprintf(stderr, "client: server is closed.\n");
                                close(sockfd);
                                exit(0);
                        }
                        recvline[strlen(recvline)] = '\0';
                        fprintf(stdout, "%s", recvline);
                }
                if (pfds[1].revents & POLLIN)
                {
                        memset(sendline, 0, sizeof(sendline));
                        n = read(STDIN_FILENO, sendline, MAXLINE);
                        if (n == 0)
                        {
                                shutdown(sockfd, SHUT_WR);
                                continue;
                        }
                        write(sockfd, sendline, n);
                }
        }
}
