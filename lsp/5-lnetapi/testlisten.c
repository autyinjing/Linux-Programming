/*
 * =====================================================================================
 *
 *       Filename:  testlisten.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 14时44分25秒
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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

static bool     stop = false;

static void handle_term(int sig)
{
        stop = true;
}

int main(int argc, char *argv[])
{
	signal(SIGTERM, handle_term);

        if (argc <= 3)
        {
                printf("Usage: %s ip_address port_number backlog\n", argv[0]);
                return 1;
        }
        const char *ip = argv[1];
        int     port = atoi(argv[2]);
        int     backlog = atoi(argv[3]);

        int     sock = socket(PF_INET, SOCK_STREAM, 0);
        assert(sock >= 0);

        /* 创建一个IPv4的套接字地址 */
        struct sockaddr_in      servaddr;
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &servaddr.sin_addr);
        servaddr.sin_port = htons(port);

        /* 绑定套接字 */
        int     ret = bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr));
        assert(ret != -1);

        /* 监听 */
        ret = listen(sock, backlog);
        assert(ret != -1);

        while ( !stop )
        {
                sleep(1);
        }

        close(sock);

	return EXIT_SUCCESS;
}

