/* ***********************************************************************

  > File Name: t_64.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Tue 23 Jan 2018 04:13:53 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main(int argc, const char* argv[])
{
    time_t t_sec = INT32_MAX;
    printf("size(time_t):%lu\n%s\n", sizeof(time_t), ctime(&t_sec));

    return 0;
}
