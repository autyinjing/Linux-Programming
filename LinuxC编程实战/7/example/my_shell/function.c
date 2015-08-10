/*
 * =====================================================================================
 *
 *       Filename:  function.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月23日 08时45分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */

#include "head.h"

/*函数说明：打印提示符*/
void print_prompt( void )
{
	printf("myshell$$ ");
}

/*函数说明：获取用户输入*/
void get_input( char *buf )
{
	int 	len = 0;
	int 	ch;

	ch = getchar();
	while ( len < 256 && ch != '\n' ) {
		buf[len++] = ch;
		ch = getchar();
	}

	if ( len == 256 ) {
		printf("command is too long \n");
		exit(-1);
	}
	buf[len++] = '\n';
	buf[len] = '\0';
}

/*函数说明：解析命令，将结果存入arglist中，命令以\n结束*/
void explain_input( char *buf, int *argcount, char arglist[100][256] )
{
	char 	*p = buf;
	char 	*q = buf;
	int 	number = 0;

	while ( 1 ) {
		if ( p[0] == '\n' )
		      break;

		if ( p[0] == ' ' )
		      p++;
		else {
			q = p;
			number = 0;
			while ( (q[0] != ' ' ) && (q[0] != '\n') ) {
				number++;
				q++;
			}
			strncpy(arglist[*argcount], p, number+1);
			arglist[*argcount][number] = '\0';
			*argcount = *argcount + 1;
			p = q;
		}
	}
}

/*函数说明：处理命令*/
void do_cmd( int argcount, char arglist[100][256] )
{
	int 		flag = 0;
	int 		how = 0;
	int 		background = 0;
	int 		status;
	int 		i;
	int 		fd;
	char 		*arg[argcount+1];
	char 		*argnext[argcount+1];
	char 		*file;
	pid_t 		pid;

	/*将命令取出*/
	for ( i = 0; i < argcount; ++i ) {
		arg[i] = (char *)arglist[i];
	}

	/*查看命令是否有后台运行符*/
	for ( i = 0; i < argcount; ++i ) {
		if ( strncmp(arg[i], "&", 1) == 0 ) {
			if ( i == argcount-1) {
				background = 1;
				arg[argcount-1] = NULL;
				break;
			} else {
				printf("wrong command\n");
				return ;
			}
		}
	}

	/*确定命令中是否有重定向，管道*/
	for ( i = 0; arg[i] != NULL; ++i ) {
		if ( strcmp(arg[i], ">") == 0 ) {
			flag++;
			how = out_redirect;
			if ( arg[i+1] == NULL )
			      flag++;
		}
		if ( strcmp(arg[i], "<") == 0 ) {
			flag++;
			how = in_redirect;
			if ( i == 0 )
			      flag++;
		}
		if ( strcmp(arg[i], "|") == 0 ) {
			flag++;
			how = have_pipe;
			if ( arg[i+1] == NULL )
			      flag++;
			if ( i == 0 )
			      flag++;
		}
	}

	/*flag大于1,说明命令中含有多个>,<,|符号，本程序不支持，或者格式不对*/
	if ( flag > 1 ) {
		printf("wrong command\n");
		return ;
	}

	if ( how == out_redirect ) {
		for ( i = 0; arg[i] != NULL; ++i ) {
			if ( strcmp(arg[i], ">") == 0 ) {
				file = arg[i+1];
				arg[i] = NULL;
			}
		}
	}
	if ( how == in_redirect ) {
		for ( i = 0; arg[i] != NULL; ++i ) {
			if ( strcmp(arg[i], "<") == 0 ) {
				file = arg[i+1];
				arg[i] = NULL;
			}
		}
	}

	if ( how == have_pipe ) {
		for ( i = 0; arg[i] != NULL; ++i ) {
			if ( strcmp(arg[i], "|") == 0 ) {
				arg[i] = NULL;
				int 	j;
				for ( j = i + 1; arg[j] != NULL; ++j ) {
					argnext[j-i-1] = arg[j];
				}
				argnext[j-i-1] = arg[j];
				break;
			}
		}
	}
	if ( (pid = fork()) < 0 ) {
		printf("fork error\n");
		return ;
	}

	switch (how) {
		case 0:
			/*不含>,<,|*/
			if ( pid == 0 ) {
				if ( !(find_command(arg[0])) ) {
					printf("%s: command not found\n", arg[0]);
					exit(0);
				}
				execvp(arg[0], arg);
				exit(0);
			}
			break;

		case 1:
			/*含有>*/
			if ( pid == 0 ) {
				if ( !(find_command(arg[0])) ) {
					printf("%s: command not found\n", arg[0]);
					exit(0);
				}
				fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
				dup2(fd, 1);
				execvp(arg[0], arg);
				exit(0);
			}
			break;

		case 2:
			/*含有<*/
			if ( pid == 0 ) {
				if ( !(find_command(arg[0])) ) {
					printf("%s: command not found\n", arg[0]);
					exit(0);
				}
				fd = open(file, O_RDONLY);
				dup2(fd, 0);
				execvp(arg[0], arg);
				exit(0);
			}
			break;

		case 3:
			/*含有|*/
			if ( pid == 0 ) {
				int 	pid2;
				int 	status2;
				int 	fd2;

				if ( (pid2 = fork()) < 0 ) {
					printf("fork2 error\n");
					return ;
				} else if ( pid2 == 0 ) {
					if ( !(find_command(arg[0])) ) {
						printf("%s: command not found\n", arg[0]);
						exit(0);
					}
					fd2 = open("/tmp/youdonotknowfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
					dup2(fd2, 1);
					execvp(arg[0], arg);
					exit(0);
				}
				if ( waitpid(pid2, &status2, 0) == -1 )
				      printf("wait for child process error\n");

				if ( !(find_command(argnext[0])) ) {
					printf("%s: command not found\n", argnext[0]);
					exit(0);
				}
				fd2 = open("/tmp/youdonotknowfile", O_RDONLY);
				dup2(fd2, 0);
				execvp(argnext[0], argnext);

				if ( remove("/tmp/youdonotknowfile") )
				      printf("remove error\n");
				exit(0);
			}
			break;

		default:
			break;
	}

	/*若命令中有后台运行符，则父进程直接返回，不等待子进程结束*/
	if ( background == 1 ) {
		printf("[process id %d]\n", pid);
		return ;
	}

	/*父进程等待子进程结束*/
	if ( waitpid(pid, &status, 0) == -1 )
	      printf("wait for child process error\n");
}

/*函数说明：查找命令中的可执行程序*/
int find_command( char *command )
{
	DIR 		*dp;
	struct dirent 	*dirp;
	char 		*path[] = { "./", "/bin", "/usr/bin", NULL };

	/*使当前目录下的程序可以运行*/
	if ( strncmp(command, "./", 2) == 0 )
	      command = command + 2;

	/*分别在当前目录、/bin和/usr/bin下查找要执行的程序*/
	int 	i = 0;
	while ( path[i] != NULL ) {
		if ( (dp = opendir(path[i])) == NULL )
		      printf("can not open /bin \n");
		while ( (dirp = readdir(dp)) != NULL ) {
			if ( strcmp(dirp->d_name, command) == 0 ) {
				closedir(dp);
				return 1;
			}
		}
		closedir(dp);
		++i;
	}
	return 0;
}
