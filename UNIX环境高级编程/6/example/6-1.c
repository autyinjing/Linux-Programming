/*
 * =====================================================================================
 *
 *       Filename:  6-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 15时52分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *getpwnam( const char *name )
{
	struct passwd 	*ptr;

	setpwent();
	while ( (ptr = getpwent()) != NULL )
	      if ( strcmp(name, ptr->pw_name) == 0 )
		    break;
	endpwent();
	return (ptr);
}
