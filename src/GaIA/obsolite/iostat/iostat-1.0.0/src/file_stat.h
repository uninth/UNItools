/* file_stat.h

   written by: Oliver Cordes 2012-07-27
   changed by: Oliver Cordes 2012-08-15


*/


#ifndef __file_stat_h
#define __file_stat_h 1


#include "config.h"


#if defined(HAVE_READ64) || defined(HAVE_WRITE64) || defined(HAVE_FREAD64) || defined(HAVE_FRITE64)
#define HAVE_RW64 1
#endif
#if defined(HAVE_OPEN64) || defined(HAVE_FOPEN64)
#define HAVE_O64 1
#endif


typedef struct{
  char    *filename;
  unsigned long long int reads;
  unsigned long long int writes;
#ifdef HAVE_RW64
  unsigned long long int reads64;
  unsigned long long int writes64;
#endif
  int      open;
#ifdef HAVE_O64
  int      open64;
#endif
} _fstat_file_info;




typedef struct{
  int nonfree;
  int fileid;
  int fd;
} _fstat_file_open;


typedef struct{
  int   nonfree;
  int   fileid;
  FILE *file;
} _fstat_file_fopen;
	       

/* overloaded function variables */

extern int     (*orig_open)     (const char *filename, int flag, ...);
extern int     (*orig_close)    (int fd);
extern ssize_t (*orig_read)     (int fd, void *buf, size_t count);
extern ssize_t (*orig_write)    (int fd, const void *buf, size_t count);

extern FILE*   (*orig_fopen)    (const char *filename, const char *mode);
extern int     (*orig_fclose)   ( FILE *file );
extern size_t  (*orig_fread)    (void *ptr, size_t size, size_t nmemb, FILE *stream);
extern size_t  (*orig_fwrite)   (const void *ptr, size_t size, size_t nmemb, FILE *stream);

#ifdef HAVE_OPEN64
extern int     (*orig_open64)   (const char *filename, int flag, ...);
#endif
#ifdef HAVE_CLOSE64
extern int     (*orig_close64)  (int fd);
#endif
#ifdef HAVE_READ64
extern ssize_t (*orig_read64)   (int fd, void *buf, size_t count);
#endif
#ifdef HAVE_WRITE64
extern ssize_t (*orig_write64)  (int fd, const void *buf, size_t count);
#endif

#ifdef HAVE_FOPEN64
extern FILE*   (*orig_fopen64)  (const char *filename, const char *mode);
#endif
#ifdef HAVE_FCLOSE64
extern int     (*orig_fclose64) ( FILE *file );
#endif
#ifdef HAVE_FREAD64
extern size_t  (*orig_fread64)  (void *ptr, size_t size, size_t nmemb, FILE *stream);
#endif
#ifdef HAVE_FWRITE64
extern size_t  (*orig_fwrite64) (const void *ptr, size_t size, size_t nmemb, FILE *stream);
#endif

extern int     (*orig_printf)   (const char *format, ... );


/* module functions */

void file_stat_init( void );
void file_stat_done( void );

/* overloaded functions for the classical open functions */
void file_stat_open( const char *filename, int fd );
void file_stat_read( int fd, unsigned long long int reads );
void file_stat_write( int fd, unsigned long long int writes );
void file_stat_close( int fd );

void file_stat_open64( const char *filename, int fd );
void file_stat_read64( int fd, unsigned long long int reads );
void file_stat_write64( int fd, unsigned long long int writes );
void file_stat_close64( int fd );


void file_stat_fopen( const char *filename, FILE *file);
void file_stat_fclose( FILE *file);
void file_stat_fread( FILE *file, unsigned long long int reads );
void file_stat_fwrite( FILE *file, unsigned long long int writes );


void file_stat_fopen64( const char *filename, FILE *file);
void file_stat_fclose64( FILE *file);
void file_stat_fread64( FILE *file, unsigned long long int reads );
void file_stat_fwrite64( FILE *file, unsigned long long int writes );


char *fstat_filename_file( FILE *file );

char *fstat_flag_str( int flag );



#endif
