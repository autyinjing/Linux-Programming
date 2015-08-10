/*
 * =====================================================================================
 *
 *       Filename:  local.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月21日 13时48分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#ifndef         _LOCAL_H
#define         _LOCAL_H

#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <ctime>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define         BUF_SIZE        1024
#define         SERVER_IP       "127.0.0.1"
#define         SERVER_PORT     8888
#define         EPOLL_TIMEOUT   -1
#define         EPOLL_SIZE      10000

#define         STR_WELCOME     "Welcome to seChat! Your ID is: Client #%d"
#define         STR_MESSAGE     "Client #%d: %s"
#define         STR_NON_CONNECT "There is only you!"
#define         EXIT            "exit"

#define         CHK(eval)       if ((eval) < 0) { perror("error: "); exit(-1); }
#define         CHK2(res, eval) if (((res) = (eval)) < 0) { perror("error: "); exit(-1); }

extern int setnonblocking(int sockfd);
extern handle_message(int newfd);

#endif
