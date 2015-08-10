/*
 * =====================================================================================
 *
 *       Filename:  testuid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年05月26日 19时57分51秒
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
	uid_t   uid = getuid();
        uid_t   euid = geteuid();
        
        printf("userid is %d, effective userid is: %d\n", uid, euid);

	return EXIT_SUCCESS;
}

