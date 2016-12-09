/* ***********************************************************************

  > File Name: modtc.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月08日 星期四 14时36分56秒

 ********************************************************************** */

#include <stdio.h>
#include <termios.h>
#include "../apue.h"

int main(int argc, const char* argv[])
{
    struct termios term;
    long vdisable;

    if (isatty(STDIN_FILENO) == 0)
        err_quit("STDIN is not a terminal device");
    if ((vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE)))
        err_quit("fpathconf error");
    if (tcgetattr(STDIN_FILENO, &term) < 0)
        err_sys("tcgetattr error");
    
    term.c_cc[VINTR] = vdisable;
    term.c_cc[VEOF] = 2;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) < 0)
        err_sys("tcsetattr error");

    return 0;
}

