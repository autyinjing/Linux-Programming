/* ***********************************************************************

  > File Name: 2-9.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月09日 星期五 15时03分08秒

 ********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFSIZE 64
#define DO_ERR(err_stat, err_info) \
    if (err_stat) { \
        perror(err_info); \
        exit(1); \
    }

int main(int argc, const char* argv[])
{
    if (argc == 1) {
        printf("Usage: ./a.out FILENAME\n");
        exit(1);
    }
    
    int fd1, fd2;
    char buff[BUFFSIZE];

    DO_ERR((fd1 = open(argv[1], O_RDONLY)) == -1, "open error");
    DO_ERR((fd2 = open(argv[1], O_WRONLY)) == -1, "open error");
    lseek(fd1, 100, SEEK_END);
    DO_ERR(read(fd1, buff, BUFFSIZE) == -1, "read error");
    printf("%s\n", buff);
    lseek(fd2, 20000, SEEK_END);
    DO_ERR(write(fd2, "testing 123...", 14) < 14, "read error");

    return 0;
}

