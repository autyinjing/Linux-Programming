/* ***********************************************************************

  > File Name: who1.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月08日 星期四 15时37分42秒

 ********************************************************************** */

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST

void show_info(struct utmp*);

int main(int argc, const char* argv[])
{
    struct utmp current_record;
    int         utmpfd;
    int         reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);
    close(utmpfd);

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
    printf("%s", ctime((time_t*)&(utbufp->ut_tv.tv_sec))+4);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}
