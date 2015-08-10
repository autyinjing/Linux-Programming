/*
 * =====================================================================================
 *
 *       Filename:  selectoob.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月27日 12时08分22秒
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
#include <sys/select.h>

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("...\n");
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);

        int ret = 0;
        struct sockaddr_in serv;
        bzero(&serv, sizeof(serv));
        serv.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &serv.sin_addr);
        serv.sin_port = htons(port);

        int listenfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(listenfd >= 0);
        ret = bind(listenfd, (struct sockaddr *)&serv, sizeof(serv));
        assert(ret != -1);
        ret = listen(listenfd, 5);
        assert(ret != -1);

        struct sockaddr_in cli;
        socklen_t clilen = sizeof(cli);
        int connfd = accept(listenfd, (struct sockaddr *)&cli, &clilen);
        if (connfd < 0)
        {
                perror("accept: ");
                close(connfd);
        }

        char buf[1024];
        fd_set read_fds;
        fd_set exce_fds;
        FD_ZERO(&read_fds);
        FD_ZERO(&exce_fds);

        while ( 1 )
        {
               
                FD_SET(connfd, &read_fds);
                FD_SET(connfd, &exce_fds);
                ret = select(connfd+1, &read_fds, NULL, &exce_fds, NULL);
                if (ret < 0)
                {
                        perror("select: ");
                        break;
                }

                if (FD_ISSET(connfd, &read_fds))
                {
                        memset(buf, '\0', sizeof(buf));
                        ret = recv(connfd, buf, sizeof(buf) - 1, 0);
                        if (ret <= 0) {
                                break;
                        } else {
                                printf("get %d bytes of normal data: %s\n", ret, buf);
                        }
                }

                if (FD_ISSET(connfd, &exce_fds))
                {
                        memset(buf, '\0', sizeof(buf));
                        ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
                        if (ret <= 0) {
                                break;
                        } else {
                                printf("get %d bytes of oob data: %s\n", ret, buf);
                        }
                }
        }
        close(connfd);
        close(listenfd);

	return EXIT_SUCCESS;
}
