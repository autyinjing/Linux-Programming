/*
 * =====================================================================================
 *
 *       Filename:  guess.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年06月16日 10时10分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char *argv[] )
{
	int 	number, guess, i = 8;

	srand(time(NULL));
	number = rand() % 100 + 1;

	printf("Please guess a number: ");

	while ( i > 0 )
	{
		scanf("%d", &guess);

		if ( guess == number )
		{
			printf("You are right!\n");
			return 0;
		}
		else if ( guess > number )
		{
			printf("Too high!\n");
		}
		else if ( guess < number )
		{
			printf("Too low!\n");
		}
		--i;
	}

	printf("Game over!\n");

	return EXIT_SUCCESS;
}
