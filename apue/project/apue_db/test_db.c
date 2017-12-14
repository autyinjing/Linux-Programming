/* ***********************************************************************

  > File Name: test_db.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Thu 14 Dec 2017 04:06:48 PM CST

 ********************************************************************** */

#include "../../apue.h"
#include "./apue_db.h"
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    DBHANDLE    db;
    if ((db = db_open("db4", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) == NULL)
        err_sys("db_open error");

    if (db_store(db, "Alpha", "data1", DB_INSERT) != 0)
        err_quit("db_store error for alpha");
    if (db_store(db, "Beta", "data for beta", DB_INSERT) != 0)
        err_quit("db_store error for beta");
    if (db_store(db, "gama", "record3", DB_INSERT) != 0)
        err_quit("db_store error for gama");

    char *rec = NULL, key[16] = {0};
    db_rewind(db);
    while ((rec = db_nextrec(db, key)) != NULL) {
        printf("%s: %s\n", key, rec);
    }

    db_close(db);
    return 0;
}
