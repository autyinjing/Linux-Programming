/*
 * =====================================================================================
 *
 *       Filename:  my_ls.c
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  2014年06月19日 11时28分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */

#ifndef _HEAD_H_
#define _HEAD_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <fcntl.h>
	#include <dirent.h>
	#include <string.h>
	#include <unistd.h>
	#include <errno.h>
	#include <grp.h>
	#include <pwd.h>
	#include <time.h>
	#include <linux/limits.h>

	#define PARAM_NONE 	0 	/*无参数*/
	#define PARAM_A 	1 	/*-a参数*/
	#define PARAM_L 	2 	/*-l参数*/
	#define MAXROWLEN 	80 	/*每行显示最多的字符数*/

#endif

static int 	g_leave_len = MAXROWLEN; 	/*一行的剩余长度，用于输出对齐*/
static int 	g_maxlen; 			/*某目录下最长文件名的长度*/
