/* ***********************************************************************

  > File Name: db.c
  > Author: Aut
  > Mail: aut@taomee.com 
  > Created Time: Tue 12 Dec 2017 05:01:00 PM CST

 ********************************************************************** */

#include "../../apue.h"
#include "./apue_db.h"
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/uio.h>

/* 索引文件使用的常量 */
#define IDXLEN_SZ       4
#define SEP             ':'
#define SPACE           ' '
#define NEWLINE         '\n'

/* 空闲链表和散列链使用的常量 */
#define PTR_SZ          4
#define PTR_MAX         999999
#define NHASH_DEF       3
#define FREE_OFF        0
#define HASH_OFF        PTR_SZ

typedef unsigned long   DBHASH;
typedef unsigned long   COUNT;

/* 数据库结构 */
typedef struct {
    int     idxfd;          /* 索引文件的描述符 */
    int     datfd;          /* 数据文件的描述符 */
    char    *idxbuf;        /* 索引文件缓冲区 */
    char    *datbuf;        /* 数据文件缓冲区 */
    char    *name;          /* 数据库名缓冲区 */

    off_t   idxoff;         /* 索引记录的偏移量 */
    size_t  idxlen;         /* 索引记录的长度 */

    off_t   datoff;         /* 数据偏移量 */
    size_t  datlen;         /* 数据长度 */

    off_t   ptrval;         /* 空闲链表指针 */
    off_t   ptroff;         /* 查找的键所在链表里面的上一个记录项的偏移量 */
    off_t   chainoff;       /* 当前key的散列表偏移量 */
    off_t   hashoff;        /* 散列表项的长度 */

    DBHASH  nhash;          /* 散列表的长度 */
    /* 计数器 */
    COUNT   cnt_delok;      /* 删除成功 */
    COUNT   cnt_delerr;     /* 删除失败 */
    COUNT   cnt_fetchok;    /* 访问成功 */
    COUNT   cnt_fetcherr;   /* 访问失败 */
    COUNT   cnt_nextrec;    /* 读取下一条成功 */
    COUNT   cnt_stor1;      /* 追加数据 */
    COUNT   cnt_stor2;      /* 在已删除key的位置插入数据 */
    COUNT   cnt_stor3;      /* 删除已存在的key后重新插入 */
    COUNT   cnt_stor4;      /* 替换已存在的key */
    COUNT   cnt_storerr;    /* 已存在，插入失败 */
} DB;

/* 内部函数 */
static DB       *_db_alloc(int);
static void     _db_dodelete(DB *);
static int      _db_find_and_lock(DB *, const char *, int);
static int      _db_findfree(DB *, int, int);
static void     _db_free(DB *);
static DBHASH   _db_hash(DB *, const char *);
static char     *_db_readdat(DB *);
static off_t    _db_readidx(DB *, off_t);
static off_t    _db_readptr(DB *, off_t);
static void     _db_writedat(DB *, const char *, off_t, int);
static void     _db_writeidx(DB *, const char *, off_t, int, off_t);
static void     _db_writeptr(DB *, off_t, off_t);

/* 打开或者创建一个数据库 */
DBHANDLE db_open(const char *pathname, int oflag, ...)
{
    DB          *db;
    int         len, mode;
    size_t      i;
    char        asciiptr[PTR_SZ + 1],
                hash[(NHASH_DEF + 1) * PTR_SZ + 2];
    struct stat statbuff;

    /* 申请需要的空间 */
    len = strlen(pathname);
    if ((db = _db_alloc(len)) == NULL)
        err_dump("db_open: _db_alloc error for DB");
    db->nhash   = NHASH_DEF;
    db->hashoff = HASH_OFF;
    strcpy(db->name, pathname);
    strcat(db->name, ".idx");

    /* 打开或者创建文件 */
    if (oflag & O_CREAT) {
        va_list ap;
        va_start(ap, oflag);
        mode = va_arg(ap, int);
        va_end(ap);

        db->idxfd = open(db->name, oflag, mode);
        strcpy(db->name + len, ".dat");
        db->datfd = open(db->name, oflag, mode);
    } else {
        db->idxfd = open(db->name, oflag);
        strcpy(db->name + len, ".dat");
        db->datfd = open(db->name, oflag);
    }

    if (db->idxfd < 0 || db->datfd < 0) {
        _db_free(db);
        return NULL;
    }

    /* 写入索引文件第一行的信息 */
    if ((oflag & (O_CREAT | O_TRUNC)) == (O_CREAT | O_TRUNC)) {
        if (writew_lock(db->idxfd, 0, SEEK_SET, 0) < 0)
            err_dump("db_open: writew_lock error");
        
        if (fstat(db->idxfd, &statbuff) < 0)
            err_sys("db_open: fstat error");

        if (statbuff.st_size == 0) {
            sprintf(asciiptr, "%*d", PTR_SZ, 0);
            hash[0] = 0;
            for (i = 0; i < NHASH_DEF + 1; ++i)
                strcat(hash, asciiptr);
            strcat(hash, "\n");
            i = strlen(hash);
            if (write(db->idxfd, hash, i) != i)
                err_dump("db_open: index file init write error");
        }
        if (un_lock(db->idxfd, 0, SEEK_SET, 0) < 0)
            err_dump("db_open: un_lock error");
    }

    db_rewind(db);
    return db;
}

/* 申请空间并且初始化DB结构 */
static DB *_db_alloc(int namelen)
{
    DB      *db;

    /* 申请空间 */
    if ((db = calloc(1, sizeof(DB))) == NULL)
        err_dump("_db_alloc: calloc error for DB");

    /* 文件描述符 */
    db->idxfd = db->datfd = -1;

    /* 文件名 */
    if ((db->name = malloc(namelen + 5)) == NULL)
        err_dump("_db_alloc: malloc error for name");

    /* 缓冲区 */
    if ((db->idxbuf = malloc(IDXLEN_MAX + 2)) == NULL)
        err_dump("_db_alloc: malloc error for index buffer");
    if ((db->datbuf = malloc(DATLEN_MAX + 2)) == NULL)
        err_dump("_db_alloc: malloc error for data buffer");

    return db;
}

/* 关闭DB句柄 */
void db_close(DBHANDLE h)
{
    _db_free((DB *)h);
}

/* 释放DB结构占用的空间 */
static void _db_free(DB *db)
{
    /* 关闭文件 */
    if (db->idxfd >= 0)
        close(db->idxfd);
    if (db->datfd >= 0)
        close(db->datfd);
    
    /* 释放缓冲区 */
    if (db->idxbuf != NULL)
        free(db->idxbuf);
    if (db->datbuf != NULL)
        free(db->datbuf);
    if (db->name != NULL)
        free(db->name);
    free(db);
}

/* 获取一个记录 */
char *db_fetch(DBHANDLE h, const char *key)
{
    DB      *db = h;
    char    *ptr;

    if (_db_find_and_lock(db, key, 0) < 0) {
        ptr = NULL;
        db->cnt_fetcherr++;
    } else {
        ptr = _db_readdat(db);
        db->cnt_fetchok++;
    }

    if (un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
        err_dump("db_fetch: unlock error");
    return ptr;
}

/* 查找指定key对应的记录 */
static int _db_find_and_lock(DB *db, const char *key, int writelock)
{
    off_t   offset, nextoffset;

    db->chainoff = (_db_hash(db, key) * PTR_SZ) + db->hashoff;
    db->ptroff = db->chainoff;

    /* 对单个散列链加锁 */
    if (writelock) {
        if (writew_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
            err_dump("_db_find_and_lock: writew_lock error");
    } else {
        if (readw_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
            err_dump("_db_find_and_lock: readw_lock error");
    }

    /* 读取散列链第一个节点的偏移量 */
    offset = _db_readptr(db, db->ptroff);

    /* 遍历散列链，查找key */
    while (offset != 0) {
        nextoffset = _db_readidx(db, offset);
        if (strcmp(db->idxbuf, key) == 0)
            break;
        db->ptroff = offset;
        offset = nextoffset;
    }

    return (offset == 0 ? -1 : 0);
}

/* 计算哈希值 */
static DBHASH _db_hash(DB *db, const char *key)
{
    DBHASH  hval = 0;
    char    c;
    int     i;

    for (i = 1; (c = *key++) != 0; ++i)
        hval += c * i;
    return (hval % db->nhash);
}

/* 读取空闲链表节点的指针值 */
static off_t _db_readptr(DB *db, off_t offset)
{
    char    asciiptr[PTR_SZ + 1];

    if (lseek(db->idxfd, offset, SEEK_SET) == -1)
        err_dump("_db_readptr: lseek error to ptr field");
    if (read(db->idxfd, asciiptr, PTR_SZ) != PTR_SZ)
        err_dump("_db_readptr: read error of ptr field");
    asciiptr[PTR_SZ] = 0;
    return (atol(asciiptr));
}

/* 读取一条索引记录 */
static off_t _db_readidx(DB *db, off_t offset)
{
    ssize_t         i;
    char            *ptr1, *ptr2;
    char            asciiptr[PTR_SZ + 1], asciilen[IDXLEN_SZ + 1];
    struct iovec    iov[2];

    /* 定位到记录的位置 */
    if ((db->idxoff = lseek(db->idxfd, offset, offset == 0 ? SEEK_CUR : SEEK_SET)) == -1)
        err_dump("_db_readidx: lseek error");
    
    /* 读取下一个节点的偏移量和索引记录长度 */
    iov[0].iov_base = asciiptr;
    iov[0].iov_len  = PTR_SZ;
    iov[1].iov_base = asciilen;
    iov[1].iov_len  = IDXLEN_SZ;
    if ((i = readv(db->idxfd, &iov[0], 2)) != PTR_SZ + IDXLEN_SZ) {
        if (i == 0 && offset == 0)  /* 读到文件尾 */
            return -1;
        err_dump("_db_readidx: readv error of index record");
    }

    asciiptr[PTR_SZ] = 0;
    db->ptrval = atol(asciiptr);

    asciilen[IDXLEN_SZ] = 0;
    if ((db->idxlen = atoi(asciilen)) < IDXLEN_MIN || db->idxlen > IDXLEN_MAX)
        err_dump("_db_readidx: invalid length");

    /* 读取索引记录 */
    if ((i = read(db->idxfd, db->idxbuf, db->idxlen)) != db->idxlen)
        err_dump("_db_readidx: read error of index record");
    if (db->idxbuf[db->idxlen-1] != NEWLINE)
        err_dump("_db_readidx: missing newline");
    db->idxbuf[db->idxlen-1] = 0;

    /* 读取数据偏移量和数据长度 */
    if ((ptr1 = strchr(db->idxbuf, SEP)) == NULL)
        err_dump("_db_readidx: missing first separator");
    *ptr1++ = 0;
    if ((ptr2 = strchr(ptr1, SEP)) == NULL)
        err_dump("_db_readidx: missing second separator");
    *ptr2++ = 0;
    if (strchr(ptr2, SEP) != NULL)
        err_dump("_db_readidx: too many separators");

    if ((db->datoff = atol(ptr1)) < 0)
        err_dump("_db_readidx: starting offset < 0");
    if ((db->datlen = atol(ptr2)) <= 0 || db->datlen > DATLEN_MAX)
        err_dump("_db_readidx: invalid length");
    return db->ptrval;
}

/* 读取数据 */
static char *_db_readdat(DB *db)
{
    if (lseek(db->datfd, db->datoff, SEEK_SET) == -1)
        err_dump("_db_readdat: lseek error");
    if (read(db->datfd, db->datbuf, db->datlen) != db->datlen)
        err_dump("_db_readdat: read error");
    if (db->datbuf[db->datlen-1] != NEWLINE)
        err_dump("_db_readdat: missing newline");
    db->datbuf[db->datlen-1] = 0;
    return db->datbuf;
}

/* 删除指定的数据 */
int db_delete(DBHANDLE h, const char *key)
{
    DB      *db = h;
    int     rc = 0;

    if (_db_find_and_lock(db, key, 1) == 0) {
        _db_dodelete(db);
        db->cnt_delok++;
    } else {
        rc = -1;
        db->cnt_delerr++;
    }
    if (un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
        err_dump("db_delete: un_lock error");
    return rc;
}

/* 执行删除操作 */
static void _db_dodelete(DB *db)
{
    int     i;
    char    *ptr;
    off_t   freeptr, saveptr;

    /* 将数据结构中索引记录和数据记录清空 */
    for (ptr = db->datbuf, i = 0; i < db->datlen - 1; i++)
        *ptr++ = SPACE;
    *ptr = 0;
    ptr = db->idxbuf;
    while (*ptr)
        *ptr++ = SPACE;

    /* 将空白内容写入文件 */
    if (writew_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
        err_dump("_db_dodelete: write_lock error");
    _db_writedat(db, db->datbuf, db->datoff, SEEK_SET);

    freeptr = _db_readptr(db, FREE_OFF);
    saveptr = db->ptrval;

    /* 将删除的索引记录放入空闲链表的首部 */
    _db_writeidx(db, db->idxbuf, db->idxoff, SEEK_SET, freeptr);
    _db_writeptr(db, FREE_OFF, db->idxoff);

    /* 将删除的索引记录的后一条记录串在前一条记录上 */
    _db_writeptr(db, db->ptroff, saveptr);

    if (un_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
        err_dump("_db_dodelete: un_lock error");
}

/* 写数据 */
static void _db_writedat(DB *db, const char *data, off_t offset, int whence)
{
    struct iovec    iov[2];
    static char     newline = NEWLINE;

    /* 往文件尾追加数据，需要锁住整个文件 */
    if (whence == SEEK_END)
        if (write_lock(db->datfd, 0, SEEK_SET, 0) < 0)
            err_dump("_db_writedat: writew_lock error");
    if ((db->datoff = lseek(db->datfd, offset, whence)) == -1)
        err_dump("_db_writedat: lseek error");
    db->datlen = strlen(data) + 1;

    iov[0].iov_base = (char *)data;
    iov[0].iov_len  = db->datlen - 1;
    iov[1].iov_base = &newline;
    iov[1].iov_len  = 1;
    if (writev(db->datfd, &iov[0], 2) != db->datlen)
        err_dump("_db_writedat: writev error of data record");
    if (whence == SEEK_END)
        if (un_lock(db->datfd, 0, SEEK_SET, 0) < 0)
            err_dump("_db_writedat: unlock error");
}

/* 写索引记录 */
static void _db_writeidx(DB *db, const char *key, off_t offset, int whence, off_t ptrval)
{
    struct iovec    iov[2];
    char            asciiptrlen[PTR_SZ + IDXLEN_SZ + 1];
    int             len;
    char            *fmt;

    /* 构造写入内容 */
    if ((db->ptrval = ptrval) < 0 || ptrval > PTR_MAX)
        err_quit("_db_writeidx: invalid ptr: %d", ptrval);
    if (sizeof(off_t) == sizeof(long long))
        fmt = "%s%c%lld%c%d\n";
    else
        fmt = "%s%c%ld%c%d\n";
    sprintf(db->idxbuf, fmt, key, SEP, db->datoff, SEP, db->datlen);
    if ((len = strlen(db->idxbuf)) < IDXLEN_MIN || len > IDXLEN_MAX)
        err_dump("_db_writeidx: invalid length");
    sprintf(asciiptrlen, "%*ld%*d", PTR_SZ, ptrval, IDXLEN_SZ, len);

    /* 如果是追加数据，需要对散列链加锁 */
    if (whence == SEEK_END)
        if (writew_lock(db->idxfd, ((db->nhash+1)*PTR_SZ)+1, SEEK_SET, 0) < 0)
            err_dump("_db_writeidx: writew_lock error");

    if ((db->idxoff = lseek(db->idxfd, offset, whence)) == -1)
        err_dump("_db_writeidx: lseek error");

    iov[0].iov_base = asciiptrlen;
    iov[0].iov_len  = PTR_SZ + IDXLEN_SZ;
    iov[1].iov_base = db->idxbuf;
    iov[1].iov_len  = len;
    if (writev(db->idxfd, &iov[0], 2) != PTR_SZ + IDXLEN_SZ + len)
        err_dump("_db_writeidx: writev error of index record");

    if (whence == SEEK_END)
        if (un_lock(db->idxfd, ((db->nhash+1)*PTR_SZ)+1, SEEK_SET, 0) < 0)
            err_dump("_db_writeidx: unlock error");
}

/* 将ptrval以空闲链表节点指针的格式写入offset指定文件位置 */
static void _db_writeptr(DB *db, off_t offset, off_t ptrval)
{
    char        asciiptr[PTR_SZ + 1];

    if (ptrval < 0 || ptrval > PTR_MAX)
        err_quit("_db_writeptr: invalid ptr: %d", ptrval);
    sprintf(asciiptr, "%*ld", PTR_SZ, ptrval);

    if (lseek(db->idxfd, offset, SEEK_SET) == -1)
        err_dump("_db_writeptr: lseek error to ptr field");
    if (write(db->idxfd, asciiptr, PTR_SZ) != PTR_SZ)
        err_dump("_db_writeptr: write error of ptr field");
}

/* 存储记录接口 */
int db_store(DBHANDLE h, const char *key, const char *data, int flag)
{
    DB      *db = h;
    int     rc, keylen, datlen;
    off_t   ptrval;

    if (flag != DB_INSERT && flag != DB_REPLACE && flag != DB_STORE) {
        errno = EINVAL;
        return -1;
    }
    keylen = strlen(key);
    datlen = strlen(data) + 1;
    if (datlen < DATLEN_MIN || datlen > DATLEN_MAX)
        err_dump("db_store: invalid data length");

    if (_db_find_and_lock(db, key, 1) < 0) {            /* 没有找到记录 */
        if (flag == DB_REPLACE) {
            rc = -1;
            db->cnt_storerr++;
            errno = ENOENT;
            goto doreturn;
        }

        ptrval = _db_readptr(db, db->chainoff);
        if (_db_findfree(db, keylen, datlen) < 0) {     
            /* 空闲链表中没有找到足够大的空记录项 */
            _db_writedat(db, data, 0, SEEK_END);
            _db_writeidx(db, key, 0, SEEK_END, ptrval);

            _db_writeptr(db, db->chainoff, db->idxoff);
            db->cnt_stor1++;
        } else {                                        
            /* 空闲链表中有一个能够容纳新记录的空记录项 */
            _db_writedat(db, data, db->datoff, SEEK_SET);
            _db_writeidx(db, key, db->idxoff, SEEK_SET, ptrval);
            _db_writeptr(db, db->chainoff, db->idxoff);
            db->cnt_stor2++;
        }
    } else {                                            /* 找到记录 */
        /* 已存在，不能插入 */
        if (flag == DB_INSERT) {                        
            rc = 1;
            db->cnt_storerr++;
            goto doreturn;
        }

        /* replace 或者 store */
        if (datlen != db->datlen) {
            _db_dodelete(db);

            ptrval = _db_readptr(db, db->chainoff);

            _db_writedat(db, data, 0, SEEK_END);
            _db_writeidx(db, key, 0, SEEK_END, ptrval);

            _db_writeptr(db, db->chainoff, db->idxoff);
            db->cnt_stor3++;
        } else {
            _db_writedat(db, data, db->datoff, SEEK_SET);
            db->cnt_stor4++;
        }
    }
    rc = 0;

doreturn:
    if (un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
        err_dump("db_store: un_lock error");
    return rc;
}

/* 从空闲链表上寻找一个长度匹配的空记录项 */
static int _db_findfree(DB *db, int keylen, int datlen)
{
    int     rc;
    off_t   offset, nextoffset, saveoffset;

    if (writew_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
        err_dump("_db_findfree: writew_lock error");

    saveoffset = FREE_OFF;
    offset = _db_readptr(db, saveoffset);

    /* 链表查询 */
    while (offset != 0) {
        nextoffset = _db_readidx(db, offset);
        if (strlen(db->idxbuf) == keylen && db->datlen == datlen)
            break;
        saveoffset = offset;
        offset = nextoffset;
    }

    if (offset == 0) {
        rc = -1;
    } else {
        _db_writeptr(db, saveoffset, db->ptrval);
        rc = 0;
    }

    if (un_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
        err_dump("_db_findfree: un_lock error");
    return rc;
}

/* 重置文件偏移量为第一条记录的起始位置 */
void db_rewind(DBHANDLE h)
{
    DB      *db = h;
    off_t   offset;

    offset = (db->nhash + 1) * PTR_SZ;
    if ((db->idxoff = lseek(db->idxfd, offset+1, SEEK_SET)) == -1)
        err_dump("db_rewind: lseek error");
}

/* 返回下一条记录 */
char *db_nextrec(DBHANDLE h, char *key)
{
    DB      *db = h;
    char    c;
    char    *ptr;

    if (readw_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
        err_dump("db_nextrec: readw_lock error");

    /* 读取一条非空索引 */
    do {
        if (_db_readidx(db, 0) < 0) {
            ptr = NULL;
            goto doreturn;
        }

        ptr = db->idxbuf;
        while ((c = *ptr++) != 0 && c == SPACE)
            ;
    } while (c == 0);

    /* 读取数据 */
    if (key != NULL)
        strcpy(key, db->idxbuf);
    ptr = _db_readdat(db);
    db->cnt_nextrec++;

doreturn:
    if (un_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
        err_dump("db_nextrec: un_lock error");
    return ptr;
}
