/*
 * =====================================================================================
 *
 *       Filename:  function.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月23日 08时32分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "function.c"

int main( int argc, char *argv[] )
{
	int 	i;
	int 	argcount = 0;
	char 	arglist[100][256];
	char 	*buf = NULL;

	buf = (char *)malloc(256);
	if ( buf == NULL ) {
		perror("malloc failed");
		exit(-1);
	}

	while (1) {
		/*将buf所指向的空间清零*/
		memset(buf, 0, 256);
		print_prompt();
		get_input(buf);

		/*若输入的命令为exit或者logout则退出程序*/
		if ( strcmp(buf, "exit\n") == 0 || strcmp(buf, "logout\n") == 0 )
		      break;
		for ( i = 0; i < 100; ++i )
		      arglist[i][0] = '\0';
		argcount = 0;
		explain_input(buf, &argcount, arglist);
		do_cmd(argcount, arglist);
	}

	if ( buf != NULL ) {
		free(buf);
		buf = NULL;
	}

	exit(0);
}
