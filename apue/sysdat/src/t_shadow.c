/* ***********************************************************************

  > File Name: t_shadow.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Tue 23 Jan 2018 03:14:02 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <shadow.h>

int main(int argc, const char* argv[])
{
    struct spwd *pSd = getspnam("root");
    if (pSd == NULL)
        printf("NULL\n");
    else
        printf("name:%s passwd:%s\n", pSd->sp_namp, pSd->sp_pwdp);

    return 0;
}
