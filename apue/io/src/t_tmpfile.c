/* ***********************************************************************

  > File Name: t_tmpfile.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Wed 03 Jan 2018 06:17:52 PM CST

 ********************************************************************** */

#include "../../apue.h"

int main(int argc, const char* argv[])
{
    char    name[L_tmpnam], line[MAXLINE];
    FILE    *fp;

    printf("%s\n", tmpnam(NULL));
    tmpnam(name);
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL)
        err_sys("tmpfile error");
    fputs("one line of output\n", fp);
    rewind(fp);
    if (fgets(line, sizeof(line), fp) == NULL)
        err_sys("fgets error");
    fputs(line, stdout);

    return 0;
}
