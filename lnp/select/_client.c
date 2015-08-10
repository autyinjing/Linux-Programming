/*
 * =====================================================================================
 *
 *       Filename:  _client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 11时17分52秒
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
	int     sockfd;
        struct sockaddr_in      servaddr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);
        servaddr.sin_port = htons(PORT);
        connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        /* 处理连接描述符 */
        cli_handle_connection(sockfd);

	return EXIT_SUCCESS;
}

void cli_handle_connection(int sockfd)
{
        char    sendline[MAXLINE], recvline[MAXLINE];
        int     maxfdp;
        fd_set  rset;
        int     n;
        
        FD_ZERO(&rset);
        for ( ; ; )
        {
                /* 添加标准输入 */
                FD_SET(STDIN_FILENO, &rset);
                /* 添加连接描述符 */
                FD_SET(sockfd, &rset);
                maxfdp = max(STDIN_FILENO, sockfd);
                /* 轮询 */
                select(maxfdp+1, &rset, NULL, NULL, NULL);
                /* 测试连接套接字是否准备就绪 */
                if (FD_ISSET(sockfd, &rset))
                {
                        memset(recvline, 0, sizeof(recvline));
                        n = read(sockfd, recvline, MAXLINE);
                        if (n == 0)
                        {
                                fprintf(stderr, "clients: server is closed.\n");
                                close(sockfd);
                                FD_CLR(sockfd, &rset);
                                exit(0);
                        }
                        recvline[strlen(recvline)] = '\0';
                        fprintf(stdout, "%s", recvline);
                }
                if (FD_ISSET(STDIN_FILENO, &rset))
                {
                        memset(sendline, 0, sizeof(sendline));
                        n = read(STDIN_FILENO, sendline, MAXLINE);
                        if (n == 0)
                        {
                                FD_CLR(STDIN_FILENO, &rset);
                                continue;
                        }
                        write(sockfd, sendline, n);
                }
        }
}
