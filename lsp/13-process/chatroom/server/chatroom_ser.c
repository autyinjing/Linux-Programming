/*
 * =====================================================================================
 *
 *       Filename:  chatroom.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月22日 09时16分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "chatroom_ser.h"

/* -------------- 全局变量定义及初始化 -------------- */
/* 各全局变量的说明位于.h文件中 */
const char *shm_name = "/my_shm";
int sig_pipefd[2];
int epollfd = 0;
int listenfd = 0;
int shmfd = 0;

char *share_mem = NULL;
struct client_data *users = NULL;
int *sub_process = NULL;
int user_count = 0;
bool stop_child = false;

/* -------------------- 函数定义 -------------------- */

/* 设置文件描述符为非阻塞 */
int setnonblocking(int fd)
{
        int old_option = fcntl(fd, F_GETFL);
        int new_option = old_option | O_NONBLOCK;
        fcntl(fd, F_SETFL, new_option);
        return old_option;
}

/* 往epoll内核事件表中注册事件 */
void addfd(int epollfd, int fd)
{
        struct epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLIN | EPOLLET;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
        setnonblocking(fd);
}

/* 信号处理函数 */
void sig_handler(int sig)
{
        int save_errno = errno;
        int msg = sig;
        send(sig_pipefd[1], (char *)&msg, 1, 0);
        errno = save_errno;
}

/* 注册信号处理函数 */
void addsig(int sig, void (*handler)(int), bool restart )
{
        struct sigaction sa;
        memset(&sa, '\0', sizeof(sa));
        sa.sa_handler = handler;
        if (restart == true)
        {
                sa.sa_flags |= SA_RESTART;
        }
        sigfillset(&sa.sa_mask);
        assert(sigaction(sig, &sa, NULL) != -1);
}

/* 释放资源 */
void del_resource()
{
        close(sig_pipefd[0]);
        close(sig_pipefd[1]);
        close(listenfd);
        close(epollfd);
        shm_unlink(shm_name);
        free(users);
        free(sub_process);
}

/* 停止一个子进程 */
void child_term_handler(int sig)
{
        stop_child = true;
}

/* 子进程的运行函数 */
int run_child(int idx, struct client_data *users, char *share_mem)
{
        struct epoll_event events[MAX_EVENT_NUMBER];
        /* 子进程使用epoll同时监听客户连接socket和与父进程通信的管道文件描述符 */
        int child_epollfd = epoll_create(5);
        assert(child_epollfd != -1);
        int connfd = users[idx].connfd;
        addfd(child_epollfd, connfd);
        int pipefd = users[idx].pipefd[1];
        addfd(child_epollfd, pipefd);
        int ret;

        /* 子进程需要设置自己的信号处理函数 */
        addsig(SIGTERM, child_term_handler, false);

        printf("Child process [%u] is running\n", getpid());
        while ( !stop_child )
        {
                int number = epoll_wait(child_epollfd, events, MAX_EVENT_NUMBER, -1);
                int i;
                if ((number < 0) && (errno != EINTR))
                {
                        printf("epoll failure\n");
                        break;
                }

                for (i = 0; i < number; ++i)
                {
                        int sockfd = events[i].data.fd;

                        /* 本子进程负责的客户连接有数据到达 */
                        if ((sockfd == connfd) && (events[i].events &EPOLLIN)) {
                                memset(share_mem + idx * BUFFER_SIZE, '\0', BUFFER_SIZE);
                                ret = recv(connfd, share_mem + idx * BUFFER_SIZE, BUFFER_SIZE-1, 0);
                                if (ret < 0) {
                                        if (errno != EAGAIN)
                                        {
                                                stop_child = true;
                                                break;
                                        }
                                } else if (ret == 0) {
                                        stop_child = true;
                                        break;
                                } else {
                                        /* 成功读取客户数据后就通知主进程（通过管道）来处理 */
                                        send(pipefd, (char *)&idx, sizeof(idx), 0);
                                }
                        } else if ((sockfd == pipefd) && (events[i].events & EPOLLIN)) {
                                /* 主进程通知本进程（通过管道）将第client个客户的数据发送到本进程负责的客户端 */
                                int client = 0;
                                /* 接收主进程发来的数据，即有客户数据到达的连接编号 */
                                ret = recv(sockfd, (char *)&client, sizeof(client), 0);
                                if (ret < 0) {
                                        if (errno != EAGAIN)
                                        {
                                                stop_child = true;
                                                break;
                                        }
                                } else if (ret == 0) {
                                        stop_child = true;
                                        break;
                                } else {
                                        send(connfd, share_mem + client * BUFFER_SIZE, BUFFER_SIZE, 0);
                                }
                        }
                }
        }
        printf("Child process [%u] is stopping!\n", getpid());

        close(connfd);
        close(pipefd);
        close(child_epollfd);
        
        return 0;
}
