/*
 * =====================================================================================
 *
 *       Filename:  testdup.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 16时32分41秒
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
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	if (argc <= 2)
        {
                printf("...");
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);

        struct sockaddr_in serv;
        bzero(&serv, sizeof(serv));
        serv.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &serv.sin_addr);
        serv.sin_port = htons(port);

        int sock = socket(PF_INET, SOCK_STREAM, 0);
        assert(sock >= 0);

        int ret = bind(sock, (struct sockaddr *)&serv, sizeof(serv));
        assert(ret != -1);

        ret = listen(sock, 5);
        assert(ret != -1);

        close(sock);

        int fd = open("dup.txt", O_CREAT | O_TRUNC, "w");
        assert(fd > 0);
        char    buf[1024];

        memset(buf, 0, sizeof(buf));
        close(STDOUT_FILENO);
        dup(fd);
        do {
                scanf("%s", buf);
                printf("%s\n", buf);
        } while (0);
        close(fd);

        //struct sockaddr_in cli;

	return EXIT_SUCCESS;
}

