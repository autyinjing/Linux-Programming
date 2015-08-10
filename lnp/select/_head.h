/*
 * =====================================================================================
 *
 *       Filename:  _head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月20日 10时24分00秒
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

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

/* ---------------宏定义--------------- */
#define         IPADDRESS       "127.0.0.1"
#define         PORT            8787
#define         MAXLINE         1024
#define         LISTENQ         5

#define         max(a, b)       ((a) > (b)) ? (a) : (b)

/* --------------函数声明-------------- */
/* 创建套接字并绑定到本地端口 */
extern int socket_bind(const char *ip, int port);

/* IO多路复用select */
extern void do_select(int listenfd);

/* 服务端处理连接 */
extern void ser_handle_connection(int connfds[], int num, fd_set *prset, fd_set *pallset);

/* 客户端处理连接 */
extern void cli_handle_connection(int sockfd);

#endif
