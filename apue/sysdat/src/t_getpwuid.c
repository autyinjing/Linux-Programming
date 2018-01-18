/* ***********************************************************************

  > File Name: t_getpwuid.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 18 Jan 2018 02:34:26 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *my_getpwnam(const char *name)
{
    struct passwd *ptr;
    setpwent();
    while ((ptr = getpwent()) != NULL)
        if (strcmp(name, ptr->pw_name) == 0)
            break;
    endpwent();
    return ptr;
}

int main(int argc, const char* argv[])
{
    /*uid_t   pw_uid;  */
    /*gid_t   pw_gid;  */
    /*char   *pw_gecos;*/
    /*char   *pw_dir;  */
    /*char   *pw_shell;*/
    /*uid_t uid;*/
    /*sscanf(argv[1], "%u", &uid);*/
    /*struct passwd *pPw = getpwuid(uid);*/
    /*struct passwd *pPw = getpwnam(argv[1]);*/
    struct passwd *pPw = my_getpwnam(argv[1]);
    if (pPw != NULL)
        printf("name:%s passwd:%s uid:%u gid:%u gecos:%s path:%s shell:%s\n", 
        pPw->pw_name, pPw->pw_passwd, pPw->pw_uid, pPw->pw_gid, pPw->pw_gecos, pPw->pw_dir, pPw->pw_shell);

    return 0;
}
