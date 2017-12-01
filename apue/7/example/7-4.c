/*
 * =====================================================================================
 *
 *       Filename:  7-4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 16时37分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include "../../apue.h"
#include <setjmp.h>

#define TOK_ADD 	5

void 	do_line( char * );
void 	cmd_add( void );
int 	get_token( void );

jmp_buf 	jmpbuffer;

int main( int argc, char *argv[] )
{
	char 	line[MAXLINE];

	if ( setjmp(jmpbuffer) != 0 )
	      printf("error");
	while ( fgets(line, MAXLINE, stdin) != NULL )
	      do_line(line);

	exit(0);
}

char 	*tok_ptr;

void do_line( char *ptr )
{
	int 	cmd;

	tok_ptr = ptr;
	while ( (cmd = get_token()) > 0 ) {
		switch (cmd) {
			case TOK_ADD:
				cmd_add();
				break;
		}
	}
}

void cmd_add( void )
{
	int 	token;

	token = get_token();
	if ( token < 0 )
	      longjmp(jmpbuffer, 1);
}

int get_token( void )
{
	return ;
}
