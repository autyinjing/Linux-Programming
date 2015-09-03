/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月22日 10时01分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include "chatroom_ser.h"

int main(int argc, char *argv[])
{
        /* 检查参数 */
	if (argc <= 2)
        {
                printf("Usage: ...\n");
                return 1;
        }
        const char *ip = argv[1];
        int port = atoi(argv[2]);

        /* 设置套接字变量 */
        int ret = 0;
        struct sockaddr_in ser_addr;
        memset(&ser_addr, '\0', sizeof(ser_addr));
        ser_addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &ser_addr.sin_addr);
        ser_addr.sin_port = htons(port);

        /* 创建套接字 */
        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        assert(listenfd >= 0);

        /* 绑定套接字 */
        ret = bind(listenfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
        assert(ret != -1);

        /* 监听套接字 */
        ret = listen(listenfd, 5);
        assert(ret != -1);

        /* 申请资源 */
        user_count = 0;
        users = (struct client_data *)malloc(sizeof(struct client_data) * USER_LIMIT+1);
        assert(users != NULL);
        sub_process = (int *)malloc(sizeof(int) * PROCESS_LIMIT);
        assert(sub_process != NULL);

        /* 初始化子进程索引数组 */
        int i;
        for (i = 0; i < PROCESS_LIMIT; ++i)
        {
                sub_process[i] = -1;
        }

        /* 注册epoll内核事件表 */
        struct epoll_event events[MAX_EVENT_NUMBER];
        epollfd = epoll_create(5);
        assert(epollfd != -1);
        addfd(epollfd, listenfd);

        /* 创建处理信号的管道 */
        ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sig_pipefd);
        assert(ret != -1);
        setnonblocking(sig_pipefd[1]);
        addfd(epollfd, sig_pipefd[0]);

        /* 添加信号处理事件 */
        addsig(SIGCHLD, sig_handler, false);
        addsig(SIGTERM, sig_handler, false);
        addsig(SIGINT, sig_handler, false);
        addsig(SIGPIPE, SIG_IGN, false);
        bool stop_server = false;
        bool terminate = false;

        /* 创建共享内存，作为所有客户socket连接的读缓存 */
        shmfd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);     /* 创建共享内存 */
        assert(shmfd != -1);
        ret = ftruncate(shmfd, USER_LIMIT * BUFFER_SIZE);       /* 调整共享内存大小为适当值 */
        assert(ret != -1);

        /* 将共享内存关联到本进程的虚拟地址空间内 */
        share_mem = (char *)mmap(NULL, USER_LIMIT * BUFFER_SIZE, PROT_READ |
                        PROT_WRITE, MAP_SHARED, shmfd, 0);
        assert(share_mem != MAP_FAILED);
        close(shmfd);

        printf("\nChatroom server is running !\n\n");
        while ( !stop_server )
        {
                int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
                if ((number < 0) && (errno != EINTR))
                {
                        printf("epoll failure\n");
                        break;
                }

                int i;
                for (i = 0; i < number; ++i)
                {
                        int sockfd = events[i].data.fd;
                        /* 新的客户连接到来 */
                        if (sockfd == listenfd) {
                                struct sockaddr_in cli_addr;
                                socklen_t cli_len = sizeof(cli_len);
                                int connfd = accept(listenfd, 
                                                (struct sockaddr *)&cli_addr, &cli_len);
                                if (connfd < 0) {
                                        printf("errno is : %d\n", errno);
                                        continue;
                                } else {
                                        char ip_buf[16];
                                        printf("Recvied a new connection, ip: %s, port: %d\n",
                                                        inet_ntop(AF_INET, &cli_addr.sin_addr, ip_buf, 16),
                                                        ntohs(cli_addr.sin_port));
                                }

                                if (user_count >= USER_LIMIT)
                                {
                                        const char *info = "Warning: too many users!\n";
                                        printf("%s", info);
                                        send(connfd, info, strlen(info), 0);
                                        close(connfd);
                                        continue;
                                }

                                /* 保存第user_count个客户连接的相关数据 */
                                users[user_count].address = cli_addr;
                                users[user_count].connfd = connfd;
                                /* 在主进程和子进程之间建立管道，以传递必要的数据 */
                                ret = socketpair(AF_UNIX, SOCK_STREAM, 0, users[user_count].pipefd);
                                assert(ret != -1);
                                pid_t pid = fork();
                                if (pid < 0) {
                                        close(connfd);
                                        continue;
                                } else if (pid == 0) {
                                        close(epollfd);
                                        close(listenfd);
                                        close(users[user_count].pipefd[0]);
                                        close(sig_pipefd[0]);
                                        close(sig_pipefd[1]);
                                        run_child(user_count, users, share_mem);
                                        munmap((void *)share_mem, USER_LIMIT * BUFFER_SIZE);
                                        exit(0);
                                } else {
                                        close(connfd);
                                        close(users[user_count].pipefd[1]);
                                        addfd(epollfd, users[user_count].pipefd[0]);
                                        users[user_count].pid = pid;
                                        /* 记录新的客户连接在数组users中的索引值，建立进程pid和该索引值之间的映射关系 */
                                        sub_process[pid] = user_count;
                                        user_count++;
                                }
                        } else if ((sockfd == sig_pipefd[0]) && (events[i].events & EPOLLIN)) {
                                /* 处理信号事件 */
                                char signals[1024];
                                ret = recv(sig_pipefd[0], signals, sizeof(signals), 0);
                                if (ret == -1) {
                                        continue;
                                } else if (ret == 0) {
                                        continue;
                                } else {
                                        int j;
                                        for (j = 0; j < ret; ++j)
                                        {
                                                switch (signals[i])
                                                {
                                                        /* 子进程退出，表示有某个客户端关闭了连接 */
                                                        case SIGCHLD:
                                                                {
                                                                        pid_t pid;
                                                                        int stat;
                                                                        while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
                                                                        {
                                                                                /* 用子进程的pid取得要关闭进程的客户连接的编号 */
                                                                                int del_user = sub_process[pid];
                                                                                sub_process[pid] = -1;
                                                                                if ((del_user < 0) || (del_user > USER_LIMIT))
                                                                                {
                                                                                        continue;
                                                                                }
                                                                                /* 清除第del_user个客户连接使用的相关数据 */
                                                                                epoll_ctl(epollfd, EPOLL_CTL_DEL, 
                                                                                                users[del_user].pipefd[0], 0);
                                                                                close(users[del_user].pipefd[0]);
                                                                                users[del_user] = users[--user_count];
                                                                                sub_process[users[del_user].pid] = del_user;
                                                                        }
                                                                        if ( terminate )
                                                                        {
                                                                                stop_server = true;
                                                                        }
                                                                        break;
                                                                }
                                                        case SIGTERM:
                                                        case SIGINT:
                                                                {
                                                                        /* 结束服务器程序 */
                                                                        printf("Kill all the child now\n");
                                                                        if (user_count == 0)
                                                                        {
                                                                                stop_server = true;
                                                                                break;
                                                                        }
                                                                        int k;
                                                                        for (k = 0; k < user_count; ++k)
                                                                        {
                                                                                int pid = users[i].pid;
                                                                                kill(pid,SIGTERM);
                                                                        }
                                                                        terminate = true;
                                                                        break;
                                                                }
                                                        default:
                                                                {
                                                                        break;
                                                                }
                                                }
                                        }
                                }
                        } else if (events[i].events & EPOLLIN) {
                                /* 某个子进程向父进程写入了数据 */
                                int child = 0;
                                /* 读取管道数据，child变量记录了是哪个客户连接有数据到达 */
                                ret = recv(sockfd, (char *)&child, sizeof(child), 0);
                                printf("read data from child [%d] accross pipe\n", child);
                                if (ret == -1) {
                                        continue;
                                } else if (ret == 0) {
                                        continue;
                                } else {
                                        /* 向除了处理第child个客户连接的子进程之外的其他子进程发送消息，通知它们有客户数据要写 */
                                        int j;
                                        for (j = 0; j < user_count; ++j)
                                        {
                                                if (users[j].pipefd[0] != sockfd)
                                                {
                                                        printf("send data to child [%d] accross pipe\n", j);
                                                        send(users[j].pipefd[0], (char *)&child,
                                                                sizeof(child), 0);
                                                }
                                        }
                                }
                        }
                }
        }
        printf("\nChatroom server is stopping!\n");
        del_resource();

	return EXIT_SUCCESS;
}
