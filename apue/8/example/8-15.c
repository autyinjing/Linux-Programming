/*
 * =====================================================================================
 *
 *       Filename:  8-15.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月26日 16时50分07秒
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
	printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());

	exit(0);
}
