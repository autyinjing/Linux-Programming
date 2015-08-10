/*
 * =====================================================================================
 *
 *       Filename:  7-6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年05月25日 16时47分50秒
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

static void 	f1(int, int, int, int);
static void 	f2(void);
static jmp_buf 	jmpbuffer;
static int 	globval;

int main( int argc, char *argv[] )
{
	int 		autoval;
	register int 	regival;
	volatile int 	volaval;
	static int 	statval;

	globval = 1;
	autoval = 2;
	regival = 3;
	volaval = 4;
	statval = 5;

	if ( setjmp(jmpbuffer) != 0 ) {
		printf("after longjmp:\n");
		printf("globval = %d, aytoval = %d, regival = %d,"
					"volaval = %d, statval = %d\n",\
					globval, autoval, regival, volaval, statval );
		exit(0);
	}
	globval = 95;
	autoval = 96;
	regival = 97;
	volaval = 98;
	statval = 99;

	f1(autoval, regival, volaval, statval);
	exit(0);
}

static void f1( int i, int j, int k, int l )
{
	printf("int f1():\n");
	printf("globval = %d, autoval = %d, regival = %d,"
				"volaval = %d, statval = %d\n",\
				globval, i, j, k, l);
	f2();
}

static void f2( void )
{
	longjmp(jmpbuffer, 1);
}
