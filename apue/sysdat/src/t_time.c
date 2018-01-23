/* ***********************************************************************

  > File Name: t_time.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Tue 23 Jan 2018 11:26:10 AM CST

 ********************************************************************** */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, const char* argv[])
{
    /*printf("now: %lu\n", time(NULL));*/

    /*struct timeval now;*/
    /*gettimeofday(&now, NULL);*/
    /*printf("%lu  %ld\n", now.tv_sec, now.tv_usec);*/

    time_t now = time(NULL);
    printf("now_sec:%lu\n", now);

    struct tm *ptm_now = localtime(&now);
    printf("time: %02d-%02d-%02d %02d:%02d:%02d\n", ptm_now->tm_year+1900, ptm_now->tm_mon+1, ptm_now->tm_mday, ptm_now->tm_hour, ptm_now->tm_min, ptm_now->tm_sec);

    char tm_buf[128];
    strftime(tm_buf, 128, "%Y-%m-%e %H:%M:%S", ptm_now);
    printf("%s\n", tm_buf);
    printf("%s", asctime(ptm_now));

    return 0;
}
