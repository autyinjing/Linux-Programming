/* ***********************************************************************

  > File Name: getopt.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 07 Dec 2017 04:27:26 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
    int c;
    char in[16];

    scanf("%s", in);

    while ((c = getopt(argc, (char * const *)argv, in)) != -1)
        printf("%c\n", c);

    return 0;
}
