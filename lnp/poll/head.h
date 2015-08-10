/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 12时00分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), linuxeryinjing@gmail.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#ifndef         _HEAD_H
#define         _HEAD_H

/* ---------------头文件--------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

/* ---------------宏定义--------------- */
#define         IPADDRESS       "127.0.0.1"
#define         PORT            8787
#define         MAXLINE         1024
#define         LISTENQ         5
#define         OPEN_MAX        1000
#define         INFTIM          -1

#define         max(a, b)       ((a) > (b)) ? (a) : (b)

/* --------------函数声明-------------- */
extern int socket_bind(const char *ip, int port);

extern void do_poll(int listenfd);

extern void ser_handle_connection(struct pollfd connfds[], int num);

extern void cli_handle_connection(int sockfd);

#endif
