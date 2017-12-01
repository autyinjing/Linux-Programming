/*
 * =====================================================================================
 *
 *       Filename:  my_ls.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年04月24日 16时52分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */

#include "../../apue.h"
#include <dirent.h>

int main( int argc, char *argv[] )
{
	DIR 		*dp;
	struct dirent 	*dirp;

	if ( argc != 2 )
	      err_quit( "Usage: ls directory_name" );

	if ( (dp = opendir(argv[1])) == NULL )
	      err_sys( "can't open %s", argv[1] );
	while ( (dirp = readdir(dp)) != NULL )
	      printf( "%s\n", dirp->d_name );
	closedir(dp);
	exit(0);
}

