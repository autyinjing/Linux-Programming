/* ***********************************************************************

  > File Name: q_52.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 04 Jan 2018 06:25:41 PM CST

 ********************************************************************** */

#include "../../apue.h"

#define MAXLINEE 4

int main(int argc, const char* argv[])
{
    char buf[MAXLINEE];

    while (fgets(buf, MAXLINEE, stdin) != NULL)
        if (fputs(buf, stdout) == EOF)
            err_sys("output error");

    if (ferror(stdin))
        err_sys("input error");

    return 0;
}
