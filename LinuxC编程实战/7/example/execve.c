/*
 * =====================================================================================
 *
 *       Filename:  execve.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月22日 13时56分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char *argv[], char **environ )
{
	pid_t 		pid;
	int 		stat_val;

	printf("Exec example!\n");
	pid = fork();
	switch (pid) {
		case -1:
			perror("Process Creation failed\n");
			exit(1);
		case 0:
			printf("Child process is running\n");
			printf("My pid = %u, parentpid = %u\n", getpid(), getppid());
			printf("uid = %d, gid = %d\n", getuid(), getgid());
			execve("processimage", argv, environ);
			printf("process never go to here!\n");
			exit(0);
		default:
			printf("Parent process is running\n");
			break;
	}

	wait(&stat_val);
	exit(0);
}
