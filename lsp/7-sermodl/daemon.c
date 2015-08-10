/*
 * =====================================================================================
 *
 *       Filename:  daemon.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 20时20分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	daemon(0, 0);
        while ( 1 )
        {
                ;
        }

	return EXIT_SUCCESS;
}
