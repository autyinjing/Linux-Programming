/*
 * =====================================================================================
 *
 *       Filename:  numof1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月24日 20时29分18秒
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

int main(int argc, char *argv[])
{
        int     count = 0, x = 8191;
        
        while ( x )
        {
                count++;
                x = x & (x - 1);
        }
        printf("%d\n", count);

	return EXIT_SUCCESS;
}
