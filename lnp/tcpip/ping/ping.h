/*
 * =====================================================================================
 *
 *       Filename:  ping.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月08日 13时49分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#ifndef PING_H
#define PING_H

/* --------------------头文件-------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netdb.h>

/* --------------------宏定义-------------------- */

#define         ICMP_SIZE       (sizeof(struct icmp))   //ICMP报文长度
#define         ICMP_ECHO       8       //回显请求标记
#define         ICMP_ECHOREPLY  0       //回显应答标记
#define         BUF_SIZE        1024    //发送/接受缓冲区大小
#define         NUM             5       //报文的发送次数

#define         UCHAR   unsigned char
#define         USHORT  unsigned short
#define         UINT    unsigned int

/* -------------------数据结构------------------- */

//ICMP报文数据结构
struct icmp
{
        UCHAR   type;   //类型
        UCHAR   code;   //代码
        USHORT  id;     //标识符
        USHORT  checksum;       //校验和
        USHORT  sequence;       //序号
        struct timeval  timestamp;      //时间戳
};

//IP首部数据结构
struct ip
{
        //主机字节序判断
#if __BYTE_ORDER == __LITTLE_ENDIAN
        UCHAR   hlen:4;         //首部长度
        UCHAR   version:4;      //版本
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        UCHAR   version:4;
        UCHAR   hlen:4;
#endif
        UCHAR   tos;    //服务类型
        UCHAR   len;    //总长度
        USHORT  id;     //标识符
        USHORT  offset; //标志和片偏移
        UCHAR   ttl;    //生存时间
        UCHAR   protocol;       //协议
        USHORT  checksum;       //校验和
        struct in_addr  ipsrc;  //32位源ip地址
        struct in_addr  ipdst;  //32位目的ip地址
};

/* --------------------全局变量-------------------- */

extern char     buf[BUF_SIZE];

/* --------------------函数声明-------------------- */

extern USHORT   checkSum(USHORT *addr, int len);        //计算校验和
extern double   timediff(struct timeval *beg, struct timeval *end);     //计算时间差
extern void     pack(struct icmp *icmp, int len);     //打包
extern int      unpack(char *buf, int len, char *addr); //拆包

#endif
