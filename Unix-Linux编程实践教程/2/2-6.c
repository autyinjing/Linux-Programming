/* ***********************************************************************

  > File Name: 2-6.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月09日 星期五 14时26分00秒

 ********************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFSIZE 50

int main(int argc, const char* argv[])
{
    if (argc == 1) {
        return 1;
    }
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[1], O_WRONLY);
    int fd3 = open(argv[1], O_RDONLY);

    char buff1[BUFFSIZE], buff3[BUFFSIZE];
    if (read(fd1, buff1, 20) == -1) {
        perror("read1 error");
        exit(1);
    }
    printf("%s\n", buff1);
    if (write(fd2, "testing 123...", 15) == -1) {
        perror("write error");
        exit(1);
    }
    if (read(fd3, buff3, 20) == -1) {
        perror("read2 error");
        exit(1);
    }
    printf("%s\n", buff3);
    if (read(fd1, buff1, 20) == -1) {
        perror("read1 error");
        exit(1);
    }
    printf("%s\n", buff1);

    return 0;
}

