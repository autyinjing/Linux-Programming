/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月19日 12时10分23秒
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
/*	struct stat 	buf;

	if ( argc < 2 ) {
		printf("my_ls <target filename>\n");
		exit(0);
	}

	if ( lstat(argv[1], &buf) == -1 ) {
		my_err("lstat", __LINE__);
	}
	display(PARAM_NONE, argv[1]);
	display(PARAM_A, argv[1]);
	display(PARAM_L, argv[1]);
	display(PARAM_A | PARAM_L, argv[1]);
*/
	do_cmd(argc, argv);

	return EXIT_SUCCESS;
}
