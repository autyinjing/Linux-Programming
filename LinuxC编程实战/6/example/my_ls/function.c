/*
 * =====================================================================================
 *
 *       Filename:  function.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月19日 11时44分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */

#include "head.h"

/*函数说明：自定义错误处理函数*/
void my_err( const char *err_string, int line )
{
	fprintf(stderr, "line:%d ", line);
	perror(err_string);
	exit(1);
}

/*函数说明：获取文件属性并打印*/
void display_attribute( struct stat buf, char *name )
{
	char 		buf_time[32];
	struct passwd 	*psd; 	/*从该结构体中获取文件所有者的用户名*/
	struct group 	*grp; 	/*从该结构体中获取文件所有者所属组的组名*/

	/*获取文件类型并打印*/
	if ( S_ISLNK(buf.st_mode) ) {
		printf("l");
	} else if ( S_ISREG(buf.st_mode) ) {
		printf("-");
	} else if ( S_ISDIR(buf.st_mode) ) {
		printf("d");
	} else if ( S_ISCHR(buf.st_mode) ) {
		printf("c");
	} else if ( S_ISBLK(buf.st_mode) ) {
		printf("b");
	} else if ( S_ISFIFO(buf.st_mode) ) {
		printf("f");
	} else if ( S_ISSOCK(buf.st_mode) ) {
		printf("s");
	}

	/*获取文件所有者的权限*/
	if ( buf.st_mode & S_IRUSR ) {
		printf("r");
	} else {
		printf("-");
	}

	if ( buf.st_mode & S_IWUSR ) {
		printf("w");
	} else {
		printf("-");
	}

	if ( buf.st_mode & S_IXUSR ) {
		printf("x");
	} else {
		printf("-");
	}

	/*获取文件所有者所属组的用户的权限*/
	if ( buf.st_mode & S_IRGRP ) {
		printf("r");
	} else {
		printf("-");
	}

	if ( buf.st_mode & S_IWGRP ) {
		printf("w");
	} else {
		printf("-");
	}

	if ( buf.st_mode & S_IXGRP ) {
		printf("x");
	} else {
		printf("-");
	}

	/*获取其他用户的权限*/
	if ( buf.st_mode & S_IROTH ) {
		printf("r");
	} else {
		printf("-");
	}

	if ( buf.st_mode & S_IWOTH ) {
		printf("w");
	} else {
		printf("-");
	}

	if ( buf.st_mode & S_IXOTH ) {
		printf("x");
	} else {
		printf("-");
	}
	
	printf("   ");

	/*根据UID与GID获取文件所有者的用户名与组名*/
	psd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	printf("%4lu ", buf.st_nlink);
	printf("%-8s", psd->pw_name);
	printf("%-8s", grp->gr_name);

	printf("%6lu", buf.st_size);
	strcpy(buf_time, ctime(&buf.st_mtime));
	buf_time[strlen(buf_time)-1] = '\0';
	printf("  %s", buf_time);

	printf("  %s\n", name);
}

/*函数说明：在没有-l参数的情况下，打印一个文件名，打印时上下行对齐*/
void display_single( char *name )
{
	int 	i, len;

	/*如果本行不足以打印一个文件名则换行*/
	if ( g_leave_len < g_maxlen ) {
		printf("\n");
		g_leave_len = MAXROWLEN;
	}

	len = strlen(name);
	len = g_maxlen - len;
	printf("%-s", name);

	for ( i = 0; i < len; ++i ) {
		printf(" ");
	}
	printf("  ");
	g_leave_len -= (g_maxlen + 2);
}

/*
 * 	函数说明：
 * 	根据命令行参数和完整路径名显示目标文件
 * 	参数flag: 命令行参数
 * 	参数pathname: 包含了文件名的路径名
 */
void display( int flag, char *pathname )
{
	int 		i, j;
	struct stat 	buf;
	char 		name[NAME_MAX + 1];

	/*从路径中解析出文件名*/
	for ( i = 0, j = 0; i < strlen(pathname); ++i ) {
		if ( pathname[i] == '/' ) {
			j = 0;
			continue;
		}
		name[j++] = pathname[i];
	}
	name[j] = '\0';

	/*用lstat而不是stat以方便解析链接文件*/
	if ( lstat(pathname, &buf) == -1 ) {
		my_err("lstat", __LINE__);
	}

	switch (flag) {
		case PARAM_NONE: 	/*没有-a和-l选项*/
			if ( name[0] != '.' ) {
				display_single(name);
			}
			break;

		case PARAM_A: 		/*只有-a选项*/
			display_single(name);
			break;

		case PARAM_L: 		/*只有-l选项*/
			if ( name[0] != '.' ) {
				display_attribute(buf, name);
			}
			break;

		case PARAM_A + PARAM_L: /*同时有-a和-l选项*/
			display_attribute(buf, name);
			break;

		default:
			break;
	}
}

/*函数说明：打印目录信息*/
void display_dir( int flag_param, char *path )
{
	DIR 		*dir;
	struct dirent 	*ptr;
	int 		count = 0;
	char 		filenames[256][PATH_MAX+1], temp[PATH_MAX+1];

	/*获取该目录下文件总数和最长文件名*/
	if ( (dir = opendir(path)) == NULL ) {
		my_err("opendir", __LINE__);
	}
	while ( (ptr = readdir(dir)) != NULL ) {
		if ( g_maxlen < strlen(ptr->d_name) )
		      g_maxlen = strlen(ptr->d_name);
		count++;
	}
	closedir(dir);

	if ( count > 256 )
	      my_err("too many files under this dir", __LINE__);

	int 	i, j, len = strlen(path);
	dir = opendir(path);
	for ( i = 0; i < count; ++i ) {
		ptr = readdir(dir);
		if ( ptr == NULL ) {
			my_err("readdir", __LINE__);
		}
		strncpy(filenames[i], path, len);
		filenames[i][len] = '\0';
		strcat(filenames[i], ptr->d_name);
		filenames[i][len+strlen(ptr->d_name)] = '\0';
	}

	int 	*index = (int *)malloc(sizeof(int)*count), tmp;

	/*初始化索引数组*/
	for ( i = 0; i < count; ++i )
	      index[i] = i;

	/*使用冒泡排序法对字符串索引排序*/
	for ( i = 0; i < count - 1; ++i )
	      for ( j = 0; j < count - i - 1; ++j )
		    if ( strcmp(filenames[j], filenames[j+1]) > 0 ) {
			    tmp = index[j];
			    index[j] = index[j+1];
			    index[j+1] = tmp;
		    }
	/*使用冒泡排序法对文件名进行排序排序后的文件名按字母顺序存放于filenames中
	for ( i = 0; i < count - 1; ++i )
	      for ( j = 0; j < count - i - 1; ++j ) {
		      if ( strcmp(filenames[j], filenames[j+1]) > 0 ) {
			      strcpy(temp, filenames[j+1]);
			      strcpy(filenames[j+1], filenames[j]);
			      strcpy(filenames[j], temp);
		      }
	      }
	      */
	for ( i = 0; i < count; ++i )
	      display(flag_param, filenames[index[i]]);
	closedir(dir);

	/*如果命令行没有-l选项，打印一个换行符*/
	if ( (flag_param & PARAM_L) == 0 )
	      printf("\n");
}

/*函数说明：处理ls命令*/
void do_cmd( int argc, char *argv[] )
{
	int 		i, j, k, num;
	char 		path[PATH_MAX+1];
	char 		param[32];
	int 		flag_param = PARAM_NONE;
	struct stat 	buf;

	/*解析命令行参数*/
	j = 0;
	num = 0;
	for ( i = 1; i < argc; ++i ) {
		if ( argv[i][0] == '-' ) {
			for ( k = 1; k < strlen(argv[i]); ++k, ++j ) {
				param[j] = argv[i][k];
			}
			++num;
		}
	}

	/*只支持参数a和l，如果有其他参数就报错*/
	for ( i = 0; i < j; ++i ) {
		if ( param[i] == 'a' ) {
			flag_param |= PARAM_A;
			continue;
		} else if ( param[i] == 'l' ) {
			flag_param |= PARAM_L;
			continue;
		} else {
			printf("my_ls: invalid option -%c\n", param[i]);
			exit(1);
		}
	}

	/*如果没有输入文件名或目录，就显示当前目录*/
	if ( (num + 1) == argc ) {
		strcpy(path, "./");
		display_dir(flag_param, path);
		return ;
	}

	i = 1;
	do {
		/*解析路径名*/
		if ( argv[i][0] == '-' ) {
			++i;
			continue;
		} else {
			strcpy(path, argv[i]);

			/*如果目标文件或目录不存在，报错并退出*/
			if ( stat(path, &buf) == -1 )
			      my_err("stat", __LINE__);

			if ( S_ISDIR(buf.st_mode) ) {
				if ( path[strlen(argv[i])-1] != '/' ) {
					path[strlen(argv[i])] = '/';
					path[strlen(argv[i])+1] = '\0';
				} else
				      path[strlen(argv[i])] = '\0';

				display_dir(flag_param, path);
				++i;
			} else {
				display(flag_param, path);
				++i;
			}
		}
	} while (i < argc );
}
