/* ***********************************************************************

  > File Name: q_51.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 04 Jan 2018 05:40:38 PM CST

 ********************************************************************** */

#include "../../apue.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void pr_buffer_type(const char *name, FILE *fp)
{
    printf("stream = %s, ", name);

    if (fp->_IO_file_flags & _IO_UNBUFFERED)
        printf("unbuffered");
    else if (fp->_IO_file_flags & _IO_LINE_BUF)
        printf("line buffered");
    else
        printf("fully buffered");
    printf(", buffer size = %ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
}

void pr_filename_by_fp(FILE *fp)
{
    int fd = fp->_fileno;
    char linkpath[1024] = {0}, filepath[1024] = {0};
    snprintf(linkpath, 1024, "/proc/self/fd/%d", fd);
    readlink(linkpath, filepath, 1023);
    printf("filename: %s\n", filepath);
}

void my_setbuf(FILE *fp, char *buf)
{
    /*int mode = _IOFBF;*/
    /*//不带缓冲*/
    /*if (buf == NULL)*/
        /*mode = _IONBF;*/
}

int main(int argc, const char* argv[])
{
    FILE *fp = fopen("aaaaa.txt", "ab");
    if (fp == NULL)
        err_sys("fopen error");
    pr_filename_by_fp(fp);

    return 0;
}
