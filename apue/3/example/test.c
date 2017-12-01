/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月11日 20时45分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */

#include "../../apue.h"

int main( int argc, char *argv[] )
{
	printf( "%u, %u, %u\n", \
				STDIN_FILENO, STDOUT_FILENO,\
				STDERR_FILENO );

	exit(0);
}
