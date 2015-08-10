/*
 * =====================================================================================
 *
 *       Filename:  echoserv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 17时41分31秒
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

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        assert(sock >= 0);

        int ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
        assert(ret != -1);

        ret = listen(sock, 5);
        assert(ret != -1);

        struct sockaddr_in cli;
        socklen_t clilen = sizeof(cli);
        int connfd = accept(sock, (struct sockaddr *)&cli, &clilen);
        if (connfd < 0) {
                perror("accept: ");
        } else {
                int pipefd[2];
                ret = pipe(pipefd);
                assert(ret != -1);
                ret = splice(connfd, NULL, pipefd[1], NULL, 32768,
                                SPLICE_F_MORE | SPLICE_F_MOVE);
                                //2);
                assert(ret != -1);
                ret = splice(pipefd[0], NULL, connfd, NULL, 32768,
                                SPLICE_F_MORE | SPLICE_F_MOVE);
                                //2);
                assert(ret != -1);
                close(connfd);
        }

        close(sock);

	return EXIT_SUCCESS;
}
