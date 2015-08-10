/*
 * =====================================================================================
 *
 *       Filename:  uid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月10日 11时59分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */

#include "../../apue.h"

int main( void )
{
	printf( "uid = %d, gid = %d\n", getuid(), getgid() );
	exit(0);
}
