/*
 * =====================================================================================
 *
 *       Filename:  ioctl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年09月03日 17时47分08秒
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
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <net/if.h>
#include <string.h>

unsigned char g_eth_name[16];
unsigned char g_macaddr[6];
unsigned int g_subnetmask;
unsigned int g_ipaddr;
unsigned int g_broadcast_ipaddr;

/* 初始化网络，获取当前网络设备的信息 */
void init_net(const char *dev)
{
        int i;
        int sock;
        struct sockaddr_in sin;
        struct ifreq ifr;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
                perror("socket");
        memset(&ifr, '\0', sizeof(ifr));
        strcpy((char *)g_eth_name, dev);
        strcpy(ifr.ifr_name, (char *)g_eth_name);
        printf("eth name:\t%s\n", g_eth_name);

        /* 获取并打印网卡地址 */
        //memset(&ifr, '\0', sizeof(ifr));
        if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0)
                perror("ioctl");
        memcpy(g_macaddr, ifr.ifr_hwaddr.sa_data, 6);

        printf("local mac:\t");
        for (i = 0; i < 5; ++i)
                printf("%2x:", g_macaddr[i]);
        printf("%2x\n", g_macaddr[i]);

        /* 获取并打印IP地址 */
        //memset(&ifr, '\0', sizeof(ifr));
        if (ioctl(sock, SIOCGIFADDR, &ifr) < 0)
                perror("ioctl");

        memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
        g_ipaddr = sin.sin_addr.s_addr;
        printf("local eth0:\t%s\n", inet_ntoa(sin.sin_addr));

        /* 获取并打印广播地址 */
        //memset(&ifr, '\0', sizeof(ifr));
        if (ioctl(sock, SIOCGIFBRDADDR, &ifr) < 0)
                perror("ioctl");

        memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
        g_broadcast_ipaddr = sin.sin_addr.s_addr;
        printf("broadcast:\t%s\n", inet_ntoa(sin.sin_addr));

        /* 获取并打印子网掩码 */
        //memset(&ifr, '\0', sizeof(ifr));
        if (ioctl(sock, SIOCGIFNETMASK, &ifr) < 0)
                perror("ioctl");
        memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
        g_subnetmask = sin.sin_addr.s_addr;
        printf("subnetmask:\t%s\n", inet_ntoa(sin.sin_addr));

        close(sock);
}

int main(int argc, char *argv[])
{
	init_net(argv[1]);

	return EXIT_SUCCESS;
}
