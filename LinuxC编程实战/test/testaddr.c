/*
 * =====================================================================================
 *
 *       Filename:  testaddr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 22时37分46秒
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

int     glob_var;

void print_addr()
{
        int     a;
        printf("addr of function var: %p\n", &a);
}

int main(int argc, char *argv[])
{
        static int      initstaticval = 0;
        static int      val;
        char    *hp;

        hp = (char *)malloc(10);
        if (hp == NULL) {
                perror("malloc");
                exit(-1);
        }
        printf("addr of main  = %p\n", main);
        printf("addr of glob  = %p\n", &glob_var);
        printf("addr of isva  = %p\n", &initstaticval);
        printf("addr of val   = %p\n", &val);
        printf("addr of hp    = %p\n", hp);
        printf("addr of fun   = %p\n", print_addr);
        print_addr();

	return EXIT_SUCCESS;
}
