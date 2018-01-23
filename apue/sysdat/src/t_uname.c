/* ***********************************************************************

  > File Name: t_uname.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Tue 23 Jan 2018 03:35:27 PM CST

 ********************************************************************** */

#include <stdio.h>
#include <sys/utsname.h>

int main(int argc, const char* argv[])
{
    struct utsname u_name;
    uname(&u_name);
    printf("sysname:%s\nnodename:%s\nrelease:%s\nversion:%s\nmachine:%s\n", 
        u_name.sysname, u_name.nodename, u_name.release, u_name.version, u_name.machine);

    return 0;
}
