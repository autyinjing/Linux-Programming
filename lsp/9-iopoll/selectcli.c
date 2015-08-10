/*
 * =====================================================================================
 *
 *       Filename:  selectecli.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月27日 12时22分34秒
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
                perror("...\n");
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

        int ret = connect(sock, (struct sockaddr *)&serv, sizeof(serv));
        assert(ret != -1);

        do {
                ret = send(sock, "normal data", strlen("noemal data") + 1, 0);
                if (ret <= 0) {
                        perror("send: ");
                        close(sock);
                        return 1;
                } else {
                        printf("send 'normal data' to server.\n");
                }
                
                sleep(1);

                ret = send(sock, "oob data", strlen("oob data") + 1, MSG_OOB);
                if (ret <= 0) {
                        perror("send: ");
                        close(sock);
                        return 1;
                } else {
                        printf("send 'oob data' to server.\n");
                }

                sleep(1);
        } while( 1 );

	return EXIT_SUCCESS;
}
