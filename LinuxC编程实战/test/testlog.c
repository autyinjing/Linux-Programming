/*
 * =====================================================================================
 *
 *       Filename:  testlog.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 19时29分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), linuxeryinjing@gmail.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	openlog(argv[0], LOG_CONS | LOG_PID, LOG_USER);
        int     count = 0;
        while ( 1 )
        {
                syslog(LOG_INFO, "%d, log info test...", count);
                count = (count + 10) % 50;
                sleep(5);
        }
        closelog();

	return EXIT_SUCCESS;
}

