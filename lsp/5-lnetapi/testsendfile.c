/*
 * =====================================================================================
 *
 *       Filename:  testsendfile.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 16时53分05秒
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
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

int main(int argc, char *argv[])
{
	if (argc <= 3)
        {
                printf("...\n");
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);
        const char *fname = argv[3];

        int fd = open(fname, O_RDONLY);
        assert(fd > 0);
        struct stat stat_buf;
        fstat(fd, &stat_buf);

        struct sockaddr_in serv;
        bzero(&serv, sizeof(serv));
        serv.sin_family = PF_INET;
        inet_pton(AF_INET, ip, &serv.sin_addr);
        serv.sin_port = htons(port);

        int sock = socket(PF_INET, SOCK_STREAM, 0);
        assert(sock >= 0);

        int ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
        assert(ret != -1);

        ret = listen(sock, 5);
        assert(ret != -1);

        struct sockaddr_in cli;
        socklen_t clilen = sizeof(cli);
        int connfd = accept(sock, (struct sockaddr *)&cli, &clilen);
        if (connfd < 0) {
                perror("connfd: ");
        } else {
                sendfile(connfd, fd, NULL, stat_buf.st_size);
                close(connfd);
        }
        close(sock);

	return EXIT_SUCCESS;
}
