/* ***********************************************************************

  > File Name: t_fwrite.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Wed 03 Jan 2018 03:44:25 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct item {
    int     id;
    double  score;
    char    nick[16];
};

int main(int argc, const char* argv[])
{
    FILE *file = fopen("aaaaa.txt", "ab");
    if (file == NULL) {
        printf("open error");
        return 1;
    }

    struct item it;
    it.id = 101219;
    it.score = 99;
    strcpy(it.nick, "aut");

    if (fwrite(&it, sizeof(struct item), 1, file) != 1) {
        printf("fwrite error");
        return 1;
    }
    fclose(file);

    struct item rit;
    FILE *rf = fopen("aaaaa.txt", "r");
    if (rf == NULL) {
        printf("open error");
        return 1;
    }
    if (fread(&rit, sizeof(struct item), 1, rf) != 1) {
        printf("fread error");
        return 1;
    }
    printf("%d\n%.2lf\n%s\n", rit.id, rit.score, rit.nick);

    return 0;
}
