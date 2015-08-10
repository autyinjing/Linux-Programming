/*
 * =====================================================================================
 *
 *       Filename:  my_chmod.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月17日 08时24分02秒
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
#include <sys/types.h>
#include <sys/stat.h>

int main( int argc, char *argv[] )
{
	int 	mode; 		//权限
	int 	mode_u;
	int 	mode_g;
	int 	mode_o;
	char 	*path;

	/*检查参数的合法性*/
	if ( argc < 3 ) {
		printf("%s <mode num> <target file>\n", argv[0]);
		exit(0);
	}

	/*获取命令行参数*/
	mode = atoi(argv[1]);
	if ( mode > 777 || mode < 0 ) {
		printf("mode num error!\n");
		exit(0);
	}
	mode_u = mode / 100;
	mode_g = (mode - (mode_u*100)) / 10;
	mode_o = mode - (mode_u*100) - (mode_g*10);
	mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;
	path = argv[2];

	if ( chmod(path, mode) == -1) {
		perror("chmod error");
		exit(1);
	}

	return EXIT_SUCCESS;
}
