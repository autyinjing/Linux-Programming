/*
 * =====================================================================================
 *
 *       Filename:  apue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年04月24日 12时19分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aut(yinjing), linuxeryinjing@gmail.com
 *        Company:  Class 1201 of Information and Computing Science
 *
 * =====================================================================================
 */

#ifndef _APUE_H
#define _APUE_H

#define _XOPEN_SOURCE 	600

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/termios.h>

#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>

#define MAXLINE 	4096

#define FILE_MODE 	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define DIR_MODE 	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void 	Sigfunc( int );

#if 	defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((Sigfunc *) - 1)
#endif

#define min(a, b) 	((a) < (b)) ? (a) : (b)
#define max(a, b) 	((a) > (b)) ? (a) : (b)

char 	*path_alloc( int * );
long 	open_max( void );
void 	clr_fl( int, int );
void 	set_fl( int, int );
void 	pr_exit( int );
void 	pr_mask( const char * );
Sigfunc *signal_intr( int, Sigfunc * );

int 	tty_cbreak( int );
int 	tty_raw( int );
int 	tty_reset( int );
/* int 	tty_atexit( void ); */
#ifdef ECHO
struct termios 	*tty_termios( void );
#endif

void 	sleep_us( unsigned int );
ssize_t readn( int, void *, size_t );
ssize_t writen( int, const void *, size_t );
void 	daemonize( const char * );

int 	s_pipe( int * );
int 	recv_fd( int, ssize_t (*func) ( int, const void *, size_t ) );
int 	send_fd( int, int );
int 	send_err( int, int, const char * );
int 	serv_listen( const char * );
int 	serv_accept( int, uid_t * );
int 	cli_conn( const char * );
int 	buf_args( char *, int (*func)( int, char ** ) );

int 	ptym_open( char *, int );
int 	ptys_open( char * );
#ifdef 	TIOCGWINSZ
pid_t 	pty_fork( int *, char *, int, const struct termios *, const struct winsize * );
#endif

int 	lock_reg( int, int, int, off_t, int, off_t );
#define read_lock( fd, offset, whence, len ) \
	lock_reg( (fd), F_SETLK, F_RDLCK, (offset), (whence), (len) )
#define readw_lock( fd, offset, whence, len ) \
	lock_reg( (fd), F_SETLKW, F_RDLCK, (offset), (whence), (len) )
#define write_lock( fd, offset, whence, len ) \
	lock_reg( (fd), F_SETLK, F_WRLCK, (offset), (whence), (len) )
#define writew_lock( fd, offset, whence, len ) \
	lock_reg( (fd), F_SETLKW, F_WRLCK, (offset), (whence), (len) )
#define un_lock( fd, offset, whence, len ) \
	lock_reg( (fd), F_SETLK, F_UNLCK, (offset), (whence), (len) )

pid_t 	lock_test( int, int, off_t, int, off_t );

#define is_read_lockable( fd, offset, whence, len ) \
	( lock_test( (fd), F_RDLCK, (offset), (whence), (len) ) == 0 )
#define is_write_lockable( fd, offset, whence, len ) \
	( lock_test( (fd), F_WRLCK, (offset), (whence), (len) ) == 0 )

void 	err_dump( const char *, ... );
void 	err_msg( const char *, ... );
void 	err_quit( const char *, ... );
void 	err_exit( int, const char *, ... );
void 	err_ret( const char *, ... );
void 	err_sys( const char *, ... );

void 	log_msg( const char *, ... );
void 	log_open( const char *, int, int );
void 	log_quit( const char *, ... );
void 	log_ret( const char *, ... );
void 	log_sys( const char *, ... );

void 	TELL_WAIT( void );
void 	TELL_PARENT( pid_t );
void 	TELL_CHILD( pid_t );
void 	WAIT_PARENT( void );
void 	WAIT_CHILD( void );
#endif


/*
输出至标准出错文件的出错处理函数 

#include <errno.h>
#include <stdarg.h>

static void err_doit( int, int, const char *, va_list );

void err_ret( const char *fmt, ... )
{
    va_list 	ap;

    va_start( ap, fmt );
    err_doit( 1, errno, fmt, ap );
    va_end( ap );
}

void err_sys( const char *fmt, ... )
{
    va_list 	ap;

    va_start( ap, fmt );
    err_doit( 1, errno, fmt, ap );
    va_end( ap );
    exit(1);
}

void err_exit( int error, const char *fmt, ... )
{
    va_list 	ap;

    va_start( ap, fmt );
    err_doit( 1, error, fmt, ap );
    va_end( ap );
    exit(1);
}

void err_dump( const char *fmt, ... )
{
    va_list 	ap;

    va_start( ap, fmt );
    err_doit( 1, errno, fmt, ap );
    va_end( ap );
    abort();
    exit(1);
}

void err_msg( const char *fmt, ... )
{
    va_list 	ap;

    va_start( ap, fmt );
    err_doit( 0, 0, fmt, ap );
    va_end( ap );
}

void err_quit( const char *fmt, ... )
{
    va_list 	ap;

    va_start( ap, fmt );
    err_doit( 0, 0, fmt, ap );
    va_end( ap );
    exit(1);
}

static void err_doit( int errnoflag, int error, const char *fmt, va_list ap )
{
    char 	buf[MAXLINE];
    vsnprintf( buf, MAXLINE, fmt, ap );
    if ( errnoflag )
          snprintf( buf+strlen(buf), MAXLINE-strlen(buf), ": %s", strerror(error) );
    strcat( buf, "\n" );
    fflush( stdout );
    fputs( buf, stderr );
    fflush( NULL );
}

用于守护进程的出错处理函数 

#include <syslog.h>

static void 	log_doit( int, int, const char *, va_list ap );
extern int 	log_to_stderr;
int 		log_to_stderr = 1;

void log_open( const char *ident, int option, int facility )
{
    if ( log_to_stderr == 0 )
          openlog( ident, option, facility );
}

void log_ret( const char *fmt, ... )
{
    va_list 	ap;
    va_start( ap, fmt );
    log_doit( 1, LOG_ERR, fmt, ap );
    va_end( ap );
}

void log_sys( const char *fmt, ... )
{
    va_list 	ap;

    va_start( ap, fmt );
    log_doit( 1, LOG_ERR, fmt, ap );
    va_end( ap );
    exit(2);
}

void log_msg( const char *fmt, ... )
{
    va_list 	ap;
    va_start( ap, fmt );
    log_doit( 0, LOG_ERR, fmt, ap );
    va_end( ap );
}

void log_quit( const char *fmt, ... )
{
    va_list 	ap;
    va_start( ap, fmt );
    log_doit( 0, LOG_ERR, fmt, ap );
    va_end( ap );
    exit(2);
}

static void log_doit( int errnoflag, int priority, const char *fmt, va_list ap )
{
    int 	errno_save;
    char 	buf[MAXLINE];

    errno_save = errno;
    vsnprintf( buf, MAXLINE, fmt, ap );
    if ( errnoflag )
          snprintf( buf+strlen(buf), MAXLINE-strlen(buf), ": %s", strerror(errno_save) );
    strcat( buf, "\n" );
    if ( log_to_stderr ) {
        fflush( stdout );
        fputs( buf, stderr );
        fflush( stderr );
    } else {
        syslog( priority, buf );
    }
}

为路径名动态地分配空间 
#ifdef PATH_MAX
static int 	pathmax = PATH_MAX;
#else
static int 	pathmax = 0;
#endif

#define SUSV3 	200112L

static long 	posix_version = 0;

#define PATH_MAX_GUESS 1024

char *path_alloc( int *sizep )
{
    char 	*ptr;
    int 	size;

    if ( posix_version == 0 )
          posix_version = sysconf(_SC_VERSION);

    if ( pathmax == 0 ) {
        errno = 0;
        if ( (pathmax = pathconf("/", _PC_PATH_MAX)) < 0 ) {
            if ( errno == 0 )
                  pathmax = PATH_MAX_GUESS;
            else
                  err_sys( "pathconf error for _PC_PATH_MAX" );
        } else {
            pathmax++;
        }
    }
    if ( posix_version < SUSV3 )
          size = pathmax + 1;
    else
          size = pathmax;

    if ( (ptr = malloc(size)) == NULL )
          err_sys( "malloc error for pathname" );

    if ( sizep != NULL )
          *sizep = size;
    return (ptr);
}

确定文件描述符数 
#ifdef OPEN_MAX
static long 	openmax = OPEN_MAX;
#else
static long 	openmax = 0;
#endif

#define OPEN_MAX_GUESS 	256

long open_max( void )
{
    if ( openmax == 0 ) {
        errno = 0;
        if ( (openmax = sysconf(_SC_OPEN_MAX)) < 0 ) {
            if ( errno == 0 )
                  openmax = OPEN_MAX_GUESS;
            else
                  err_sys( "sysconf error for _SC_OPEN_MAX" );
        }
    }
    return (openmax);
}

void pr_exit( int status )
{
    if ( WIFEXITED(status) )
          printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if ( WIFSIGNALED(status) )
          printf("abnormal termination, singal number = %d%s\n", WTERMSIG(status), 
#ifdef WCOREDUMP
                      WCOREDUMP(status) ? " (core file generated)" : "");
#else
    "");
#endif
    else if ( WIFSTOPPED(status) )
          printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

为进程打印信号屏蔽字 
void pr_mask( const char *str )
{
    sigset_t 	sigset;
    int 		errno_save;

    errno_save = errno;
    if ( sigprocmask(0, NULL, &sigset) < 0 )
          err_sys("sigprocmask error");

    printf("%s", str);

    if (sigismember(&sigset, SIGINT))
          printf("SIGINT ");
    if (sigismember(&sigset, SIGQUIT))
          printf("SIGQUIT ");
    if (sigismember(&sigset, SIGUSR1))
          printf("SIGUSR1 ");
    if (sigismember(&sigset, SIGALRM))
          printf("SIGALRM ");

    printf("\n");
    errno = errno_save;
} */
