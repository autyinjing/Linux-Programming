/* ***********************************************************************

  > File Name: daemonize.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Wed 29 Nov 2017 03:35:25 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <fcntl.h>

void daemonize()
{
    //创建子进程，退出父进程，保证创建会话的进程不是组长进程
    if (fork() != 0)
        exit(0);

    //创建新会话
    if (setsid() == -1)
        perror("setsid");

    //再次创建子进程，保证新的进程不是会话首进程，不能申请终端
    if (fork() != 0)
        exit(0);

    //修改默认工作目录，避免当前目录被卸载
    if (chdir("/home/aut") == -1)
        perror("chdir");

    //重置文件掩码
    umask(0);

    //处理信号
    signal(SIGHUP, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);

    //获取并关闭已打开的文件描述符
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1)
        perror("getrlimit");
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    int i;
    for (i = 3; i < rl.rlim_max; ++i)
        close(i);

    //将标准输入、标准输出、标准错误重定向到/dev/null
    int fd;
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO)
            close(fd);
    }
}

int main(int argc, const char* argv[])
{
    /*daemonize();*/

    int fd = open("/home/aut/tmp/daemonized.log", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd == -1)
        perror("open");

    int i;
    for (i = 0; i < 300; ++i) {
        write(fd, "Hello World! \n", 15);
        sleep(2);
    }

    close(fd);
    return 0;
}
