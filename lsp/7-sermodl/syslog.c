/*
 * =====================================================================================
 *
 *       Filename:  syslog.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月09日 20时05分32秒
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
#include <syslog.h>

int main(int argc, char *argv[])
{
	openlog("Honey", LOG_PID | LOG_CONS, 0);
        syslog(LOG_DEBUG, "This is a test message by %s\n", argv[0]);
        closelog();

	return EXIT_SUCCESS;
}
