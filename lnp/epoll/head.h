/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 14时58分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#ifndef         _HEAD_H
#define         _HEAD_H

/* ---------------头文件--------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#define         IPADDRESS       "127.0.0.1"
#define         PORT            8787
#define         MAXSIZE         1024
#define         LISTENQ         5
#define         FDSIZE          1000
#define         EPOLLEVENTS     100

#endif
