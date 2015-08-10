/*
 * =====================================================================================
 *
 *       Filename:  pid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月10日 11时43分51秒
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
	printf( "hello world from process ID %d\n", getpid() );

	exit(0);
}
