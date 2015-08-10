/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月08日 18时04分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "ping.h" 

int main(int argc, char *argv[])
{
	struct hostent *host;
        struct icmp sendicmp;
        struct sockaddr_in from;
        struct sockaddr_in to;
        socklen_t fromlen = 0;
        int sockfd;
        int nsend = 0;
        int nrecv = 0;
        int i, n;
        in_addr_t inaddr;

        memset(&from, 0, sizeof(from));
        memset(&to, 0, sizeof(to));

        if (argc < 2)
        {
                printf("Usage: %s hostname/IP address \n", argv[0]);
                exit(1);
        }

        /* 创建原始套接字 */
        if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
        {
                perror("socket");
                exit(1);
        }

        /* 设置目的地址信息 */
        to.sin_family = AF_INET;

        /* 判断是域名还是ip地址 */
        if ((inaddr = inet_addr(argv[1])) == INADDR_NONE) {     //域名
                if ((host = gethostbyname(argv[1])) == NULL)
                {
                        perror("gethostbyname");
                        exit(1);
                }
                to.sin_addr = *(struct in_addr *)host->h_addr_list[0];
        } else {        //ip地址
                to.sin_addr.s_addr = inaddr;
        }

        /* 输出域名、ip地址信息 */
        printf("ping %s (%s) : %lu bytes of data.\n", argv[1], inet_ntoa(to.sin_addr), ICMP_SIZE);

        /* 循环发送报文、接收报文 */
        for (i = 0; i < NUM; i++)
        {
                nsend++;
                memset(&sendicmp, 0, ICMP_SIZE);
                pack(&sendicmp, nsend);

                /* 发送报文 */
                if (sendto(sockfd, &sendicmp, ICMP_SIZE, 0,
                                        (struct sockaddr *)&to, sizeof(to)) == -1)
                {
                        perror("sendto");
                        continue;
                }
                printf("send success!\n");

                /* 接收报文 */
                if ((n = recvfrom(sockfd, buf, BUF_SIZE, 0, 
                                                (struct sockaddr *)&from, &fromlen)) < 0)
                {
                        perror("recvfrom");
                        continue;
                }

                printf("recv success!\n");
                nrecv++;
                if (unpack(buf, n, inet_ntoa(from.sin_addr)) == -1)
                        perror("unpack");
                
                sleep(1);
        }

        /* 输出统计信息 */
        printf("--- %s ping statistics ---\n", argv[1]);
        printf("%d packets transmitted, %d received, %%%d packet loss\n",
                        nsend, nrecv, (nsend - nrecv) / nsend * 100);

	return EXIT_SUCCESS;
}
