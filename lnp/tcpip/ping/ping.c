/*
 * =====================================================================================
 *
 *       Filename:  ping.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月08日 14时13分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "ping.h"

/* -------------------全局变量------------------- */

char    buf[BUF_SIZE] = { 0 };

/* -------------------函数定义------------------- */

USHORT checkSum(USHORT *addr, int len)
{
        UINT    sum = 0;

        //按照两个字节一组求和
        while (len > 1)
        {
                sum += *addr++;
                len -= 2;
        }

        //处理剩下的一个字节（如果有的话）
        if (len == 1)
                sum += *(UCHAR *)addr;

        //将32位的高16位与低16位相加
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);

        return (USHORT) ~sum;
}

double timediff(struct timeval *begin, struct timeval *end)
{
        int     n;

        n = (end->tv_sec - begin->tv_sec) * 1000000
                + (end->tv_usec - begin->tv_usec);

        return (double)(n) / 1000.0;
}

void pack(struct icmp *icmp, int sequence)
{
        icmp->type = ICMP_ECHO;
        icmp->code = 0;
        icmp->checksum = 0;
        icmp->id = getpid();
        icmp->sequence = sequence;
        gettimeofday(&icmp->timestamp, 0);
        icmp->checksum = checkSum((USHORT *)icmp, ICMP_SIZE);
}

int unpack(char *buf, int len, char *addr)
{
        int ip_head_len;
        struct ip *ip;
        struct icmp *icmp;
        double rtt;     //记录往返时间
        struct timeval end;     //记录接收报文的时间戳

        ip = (struct ip *)buf;

        //计算ip首部长度，即ip首部的长度标识乘4
        ip_head_len = ip->hlen << 2;

        //越过ip首部，指向ICMP报文
        icmp = (struct icmp *)(buf + ip_head_len);

        //ICMP报文的总长度
        len -= ip_head_len;

        //如果小于ICMP报文首部长度8
        if (len < 8)
        {
                printf("ICMP packets\'s length is less than 8\n");
                return -1;
        }

        //确保是我们所发的ICMP ECHO回应
        if (icmp->type != ICMP_ECHOREPLY ||
                        icmp->id != getpid())
        {
                printf("ICMP packets are not send by us. \n");
                return -1;
        }

        //计算往返时间
        gettimeofday(&end, 0);
        rtt = timediff(&icmp->timestamp, &end);

        //打印ttl, rtt, seq
        printf("%d byte from %s: icmp_seq=%u ttl=%d rtt=%fms \n",
                        len, addr, icmp->sequence, ip->ttl, rtt);

        return 0;
}
