/* ***********************************************************************

  > File Name: 2-10.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月09日 星期五 15时52分10秒

 ********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <utmp.h>

#include "../Common.hpp"

void show_info(struct utmp* utbufp);

int main(int argc, const char* argv[])
{
    struct utmp current_record;
    int     utmpfd;
    int     reclen = sizeof(current_record);

    DO_ERR((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1, UTMP_FILE);
    while (read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);
    close(utmpfd);

    return 0;
}

void show_info(struct utmp* utbufp)
{
    if (utbufp->ut_type != LOGIN_PROCESS)
        return;
    printf("%s\n", utbufp->ut_name);
}
