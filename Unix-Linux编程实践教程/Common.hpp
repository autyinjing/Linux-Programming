/* ***********************************************************************

  > File Name: ../Common.hpp
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: 2016年12月09日 星期五 15时35分19秒

 ********************************************************************** */

#ifndef DO_ERR

#include <stdio.h>
#include <stdlib.h>

#define DO_ERR(err_stat, err_info) \
    if (err_stat) { \
        perror(err_info); \
        exit(1); \
    }

#endif  //end of DO_ERR
