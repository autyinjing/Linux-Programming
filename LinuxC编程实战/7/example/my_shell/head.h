/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月23日 08时24分03秒
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
	#include <unistd.h>
	#include <string.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <fcntl.h>
	#include <sys/wait.h>
	#include <dirent.h>

	#define normal 		0 	/*一般的命令*/
	#define out_redirect 	1 	/*输出重定向*/
	#define in_redirect 	2  	/*输入重定向*/
	#define have_pipe 	3 	/*命令中有管道*/

#endif

static void 	print_prompt( void ); 				/*打印提示符*/
static void 	get_input( char * );  				/*得到输入的命令*/
static void 	explain_input( char *, int *, char a[][256] ); 	/*解析命令*/
static void  	do_cmd( int, char a[][256] ); 			/*执行命令*/
static int 	find_command( char * ); 			/*查找命令中的可执行程序*/
