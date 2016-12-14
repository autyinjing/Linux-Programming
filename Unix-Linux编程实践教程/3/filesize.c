/* ***********************************************************************

  > File Name: filesize.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月14日 星期三 15时19分11秒

 ********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, const char* argv[])
{
    struct stat infobuf;
    if (stat("/etc/passwd", &infobuf) == -1)
        perror("/etc/passwd");
    else
        printf("The size of /etc/passwd is %ld\n", infobuf.st_size);

    return 0;
}

