/* ***********************************************************************

  > File Name: xxx.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 07 Dec 2017 02:42:08 PM CST

 ********************************************************************** */

#include <stdio.h>

#ifndef GET_MIN
#define GET_MIN(_a, _b)  ((_a) > (_b)) ? (_b) : (_a) 
#endif  //end of GET_MIN

int main(int argc, const char* argv[])
{
    int a = 20;
    a = GET_MIN(a, 10);

    return 0;
}
