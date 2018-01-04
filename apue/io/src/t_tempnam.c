/* ***********************************************************************

  > File Name: t_tempnam.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 04 Jan 2018 02:59:04 PM CST

 ********************************************************************** */

#include "../../apue.h"

int main(int argc, const char* argv[])
{
    if (argc != 3)
        err_quit("usage: a.out <dir> <pre>");

    printf("%s\n", tempnam(argv[1][0] != ' ' ? argv[1] : NULL, argv[2][0] != ' ' ? argv[2] : NULL));

    return 0;
}
