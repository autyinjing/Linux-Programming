/* ***********************************************************************

  > File Name: who3.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月08日 星期四 17时07分59秒

 ********************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include "./utmplib.c"

#define SHOWHOST

void show_info(struct utmp*);

int main(int argc, const char* argv[])
{
    struct utmp *utbufp;

    if (utmp_open(UTMP_FILE) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }
    while ((utbufp = utmp_next()) != NULLUT)
        show_info(utbufp);
    utmp_close();

    return 0;
}

void show_info(struct utmp* utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;

    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    printf("%15.15s", ctime((time_t*)&(utbufp->ut_tv.tv_sec))+4);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}
