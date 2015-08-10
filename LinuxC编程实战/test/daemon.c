/*
 * =====================================================================================
 *
 *       Filename:  daemon.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 21时52分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), linuxeryinjing@gmail.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>

int init_daemon(void)
{
        pid_t   pid;
        int     i;

        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGHUP, SIG_IGN);

        pid = fork();
        if (pid > 0) {
                exit(0);
        } else if (pid < 0) {
                return -1;
        }

        setsid();

        pid = fork();
        if (pid > 0) {
                exit(0);
        } else if (pid < 0) {
                return -1;
        }

        for (i = 0; i < NOFILE; close(i++));

        chdir("/");

        umask(0);

        signal(SIGCHLD, SIG_IGN);

        return 0;
}

int main(int argc, char *argv[])
{	
        init_daemon();
        
        while ( 1 )
        {
                int     fd = open("/home/honey/test.txt", O_CREAT | O_TRUNC, 0744);

                if (fd < 0) {
                        perror("open");
                        exit(-1);
                }
                write(fd, "hello daemon!\n", sizeof("hello daemon!\n"));
                sleep(2);
                close(fd);
        }

	return EXIT_SUCCESS;
}
