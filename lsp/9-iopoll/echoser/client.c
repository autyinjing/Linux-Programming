/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月29日 15时32分31秒
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
        socklen_t servlen = sizeof(serv);
        serv.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &serv.sin_addr);
        serv.sin_port = htons(port);

        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        //assert(sock < 0);

        //int ret = connect(sock, (struct sockaddr *)&serv, sizeof(serv));
        //assert(ret != -1);

        while ( 1 )
        {
                char    send_buf[1024], recv_buf[1024];
                
                memset(send_buf, 0, sizeof(send_buf));
                fgets(send_buf, 1023, stdin);
                int ret = sendto(sock, send_buf, strlen(send_buf), 0, (struct sockaddr *)&serv, servlen);
                if (ret < strlen(send_buf))
                {
                        perror("send: ");
                        close(sock);
                        exit(1);
                }
                memset(recv_buf, 0, sizeof(recv_buf));
                ret = recvfrom(sock, recv_buf, 1023, 0, (struct sockaddr *)&serv, &servlen);
                if (ret == 0) {
                        printf("Server closed.\n");
                        break;
                } else {
                        printf("Recv from server: %s\n", recv_buf);
                }
        }
        close(sock);

	return EXIT_SUCCESS;
}
