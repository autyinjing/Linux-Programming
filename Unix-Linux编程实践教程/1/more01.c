/* ***********************************************************************

  > File Name: more01.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月08日 星期四 11时51分25秒

 ********************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);

int main(int argc, const char* argv[])
{
    FILE *fp = NULL;
    if (argc == 1) {
        do_more(stdin);
    } else {
        while (--argc)
            if ((fp = fopen(*++argv, "r")) != NULL) {
                do_more(fp);
                fclose(fp);
            } else {
                exit(1);
            }
    }

    return 0;
}

void do_more(FILE* fp)
{
    char line[LINELEN];
    int num_of_lines = 0;
    int reply = 0;
    FILE* fp_tty = fopen("/dev/tty", "r");
    if (fp_tty == NULL)
        exit(1);
    while (fgets(line, LINELEN, fp))
    {
        if (num_of_lines == PAGELEN) {
            reply = see_more(fp_tty);
            if (reply == 0)
                break;
            num_of_lines -= reply;
        }
        if (fputs(line, stdout) == EOF)
            exit(1);
        ++num_of_lines;
    }
}

int see_more(FILE* cmd)
{
    int c = 0;
    printf("\033[7m more? \033[m");
    while ((c = getc(cmd)) != EOF)
    {
        if (c == 'q')
            return 0;
        if (c == ' ')
            return PAGELEN;
        if (c == '\n')
            return 1;
    }
    return 0;
}
