/*
 * =====================================================================================
 *
 *       Filename:  chatroom.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月22日 08时42分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#ifndef CHATROOM_H
#define CHATROOM_H

/* -------------------- Head File -------------------- */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

/* ----------------- Macro Definition ---------------- */

#define USER_LIMIT 5            /* 最大在线用户数 */
#define BUFFER_SIZE 1024        /* 用户读缓冲的大小 */
#define FD_LIMIT 65535          /* 可以打开的最大文件描述符数 */
#define MAX_EVENT_NUMBER 1024   /* epoll的最大注册事件数 */
#define PROCESS_LIMIT 65536     /* 打开的最大进程数 */

/* ------------------ Data Structure ----------------- */

struct client_data
{
        struct sockaddr_in address;     /* 客户端的socket地址 */
        int connfd;                     /* socket文件描述符 */
        pid_t pid;                      /* 处理这个连接的子进程的PID */
        int pipefd[2];                  /* 和父进程通信用的管道 */
}; /* 处理客户端连接的数据结构 */

/* ---------------- Global Variable ------------------ */

extern const char *shm_name;    /* 共享内存的文件路径 */
extern int sig_pipefd[2];       /* 主进程用于处理信号的管道 */
extern int epollfd;             /* 主进程的epoll内核事件表描述符 */
extern int listenfd;            /* 主进程的监听socket描述符 */
extern int shmfd;               /* 标记共享内存的键值 */

extern struct client_data *users;       /* 客户连接数组，进程用客户连接的编号来索引这个数组，即可得到相关的客户连接数据 */
extern char *share_mem;         /* 共享内存的起始地址 */
extern int *sub_process;        /* 子进程和客户连接的映射关系表，用进程的PID来索引这个数组，即可取得该进程所处理的客户连接的编号 */
extern int user_count;          /* 当前客户数量 */
extern bool stop_child;         /* 标记是否终止子进程 */

/* -------------- Function declaration --------------- */

extern int setnonblocking(int fd);              /* 设置文件描述符为非阻塞 */
extern void addfd(int epollfd, int fd);         /* 往epoll内核事件表中注册事件 */
extern void sig_handler(int sig);               /* 信号处理函数 */
extern void addsig(int sig, void (*handler)(int), bool restart);        /* 注册信号处理函数 */
extern void del_resource();                     /* 释放系统资源 */
extern void child_term_handler(int sig);        /* 终止一个子进程 */
extern int run_child(int idx, struct client_data *users, char *share_mem);      /* 子进程的运行函数 */

#endif
