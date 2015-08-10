/*
 * =====================================================================================
 *
 *       Filename:  testsprintf.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 18时53分13秒
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
#include <string.h>

int main(int argc, char *argv[])
{
        double  d;
        char    str[10] = "3.14";

        fprintf(stdout, "str = %s\n", str);
        sscanf(str, "%lf", &d);
        fprintf(stdout, "d = %lf\n", d);
        memset(str, '\0', sizeof(str));
        fprintf(stdout, "str = %s\n", str);
        sprintf(str, "%lf", d);
        fprintf(stdout, "str = %s\n", str);

	return EXIT_SUCCESS;
}
