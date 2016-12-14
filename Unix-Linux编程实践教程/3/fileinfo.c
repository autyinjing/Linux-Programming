/* ***********************************************************************

  > File Name: fileinfo.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月14日 星期三 15时21分34秒

 ********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void show_stat_info(const char *fname, struct stat *buf);

int main(int argc, const char* argv[])
{
    struct stat info;

    if (argc > 1) 
    {
        if (stat(argv[1], &info) != -1) {
            show_stat_info(argv[1], &info);
            return 0;
        } else {
            perror(argv[1]);
        }
    }

    return 0;
}

void show_stat_info(const char *fname, struct stat *buf)
{
    printf("    mode: %d\n", buf->st_mode);
    printf("   links: %ld\n", buf->st_nlink);
    printf("    user: %d\n", buf->st_uid);
    printf("   group: %d\n", buf->st_gid);
    printf("    size: %ld\n", buf->st_size);
    printf(" modtime: %ld\n", buf->st_mtime);
    printf("    name: %s\n", fname);
}
