/*
 * =====================================================================================
 *
 *       Filename:  bootuser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月10日 11时47分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  aut (yinjing), autyinjing@126.com
 *        Company:  Information and Computing Science 1201
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

static bool switch_to_user( uid_t user_id, gid_t gp_id )
{
        /* 先确保目标用户不是root */
        if ((user_id == 0) && (gp_id == 0))
        {
                printf("目标用户已经是root！\n");
                return false;
        }
        /* 确保当前用户是合法用户:root或者目标用户 */
        gid_t gid = getgid();
        uid_t uid = getuid();
        if (((gid != 0) || (uid != 0)) && ((gid != gp_id) || (uid != user_id)))
        {
                printf("当前用户为非法用户！\n");
                return false;
        }
        /* 如果不是root，则已经是目标用户 */
        if (uid != 0)
        {
                printf("已经是目标用户！\n");
                return true;
        }

        /* 切换到目标用户 */
        if ((setgid(gp_id) < 0) || (setuid(user_id) < 0))
        {
                printf("切换失败！\n");
                return false;
        }

        return true;
}

int main(int argc, char *argv[])
{
        uid_t uid = getuid();
        gid_t gid = getgid();

        printf("uid: %u, gid: %u\n", uid, gid);
	if (switch_to_user(1000, 1000) == false) {
                printf("switch falid!\n");
        } else {
                printf("switch success!\n");
        }
        printf("uid: %u, gid: %u\n", getuid(), getgid());

        while ( 1 )
        {
                ;
        }

	return EXIT_SUCCESS;
}
