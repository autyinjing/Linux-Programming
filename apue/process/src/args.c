/* ***********************************************************************

  > File Name: args.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Tue 05 Dec 2017 11:56:59 AM CST

 ********************************************************************** */

#include "../../apue.h"

int main(int argc, const char* argv[])
{
    int i;
    /*for (i = 0; i < argc; ++i)*/
    for (i = 0; argv[i] != NULL; ++i)
        printf("argv[%d]: %s\n", i, argv[i]);

    return 0;
}
