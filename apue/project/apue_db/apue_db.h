/* ***********************************************************************

  > File Name: apue_db.h
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Tue 12 Dec 2017 04:49:37 PM CST

 ********************************************************************** */

#ifndef _APUE_DB_H
#define _APUE_DB_H

typedef void * DBHANDLE;

DBHANDLE    db_open(const char *, int, ...);
void        db_close(DBHANDLE);
char        *db_fetch(DBHANDLE, const char *);
int         db_store(DBHANDLE, const char *, const char *, int);
int         db_delete(DBHANDLE, const char *);
void        db_rewind(DBHANDLE);
char        *db_nextrec(DBHANDLE, char *);

/*
 * db_store使用的标记
 */
#define DB_INSERT       1
#define DB_REPLACE      2
#define DB_STORE        3

/*
 * 一些上限值
 */
#define IDXLEN_MIN      6
#define IDXLEN_MAX      1024
#define DATLEN_MIN      2
#define DATLEN_MAX      1024

#endif  /* _APUE_DB_H */
