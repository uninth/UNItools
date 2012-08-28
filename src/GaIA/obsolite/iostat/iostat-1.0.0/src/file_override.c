/* file_override.c

   written by: Oliver Cordes 2012-08-02
   changed by: Oliver Cordes 2014-06-09

*/

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

#include "config.h"
#include "file_stat.h"
#include "logfile.h"
#include "params.h"



/* open/close/read/write overloading functions */ 

/* standard open routine */

#ifdef IS_DARWIN
int open$__interposed__( const char *filename, int flag, ... )
#else
int open ( const char *filename, int flag, ...)
#endif
{
  va_list ap;
  int     res;
  void   *arg;

  va_start( ap, flag );
  arg = va_arg(ap, void *);
  va_end( ap );

  /* do some sanity checks */
  if ( orig_open == NULL )
    {
      printf( "Preinit function open called!\n" );
      orig_open = dlsym( RTLD_NEXT, "open" );
      return orig_open( filename, flag, arg );
    }

  res = orig_open( filename, flag, arg );

  logfile_write( "open: filename='%s' mode=%i (%s) fd=%i", 
		 filename, flag, fstat_flag_str( flag ), res );

  file_stat_open( filename, res );
  return( res );
} 




/* standard close routine */

#ifdef IS_DARWIN
int close$__interposed__( int fd )
#else
int close( int fd )
#endif
{
  int res;

  /* do some sanity checks */
  if ( orig_close == NULL )
    {
      printf( "Preinit function close called!\n" );
      orig_open = dlsym( RTLD_NEXT, "close" );
      return orig_close( fd );
    }

  res = orig_close( fd );
  logfile_write( "close: fd=%i result=%i", fd, res );
  file_stat_close( fd );
  return res;
}


/* standard read routine */

#ifdef IS_DARWIN
ssize_t read$__interposed__(int fd, void *buf, size_t count)
#else
ssize_t read(int fd, void *buf, size_t count)
#endif
{
  ssize_t res;

  res = orig_read( fd, buf, count );
  
  logfile_write( "read: fd=%i req=%i read=%i", fd, count, res ); 
  file_stat_read( fd, res );

  return res;
}


/* standard write routine */

#ifdef IS_DARWIN
ssize_t write$__interposed__(int fd, const void *buf, size_t count)
#else
ssize_t write(int fd, const void *buf, size_t count)
#endif
{
  ssize_t res;

  res = orig_write( fd, buf, count );

  logfile_write( "write: fd=%i req=%i read=%i", fd, count, res ); 
  file_stat_write( fd, res );

  return res;
}



/* open64/close64/read64/write64 overloading functions */

#ifdef HAVE_OPEN64
int open64( const char *filename, int flag, ...)
{
  va_list ap;
  int     res;
  void   *arg;

  va_start( ap, flag );
  arg = va_arg(ap, void *);
  va_end( ap );


  /* do some sanity checks */
  if ( orig_open64 == NULL )
    {
      printf( "Preinit function open64 called!\n" );
      orig_open64 = dlsym( RTLD_NEXT, "open64" );
      return orig_open64( filename, flag, ap );
    }

  res = orig_open64( filename, flag, ap );

  logfile_write( "open: filename='%s' mode=%i (%s) fd=%i", 
		 filename, flag, fstat_flag_str( flag ), res );

  file_stat_open64( filename, res );

  return( res );
}
#endif


#ifdef HAVE_CLOSE64
int close64( int fd )
{
  int res;

  /* do some sanity checks */
  if ( orig_close64 == NULL )
    {
      printf( "Preinit function close called!\n" );
      orig_open64 = dlsym( RTLD_NEXT, "close64" );
      return orig_close64( fd );
    }

  res = orig_close64( fd );
  logfile_write( "close64: fd=%i result=%i", fd, res );
  file_stat_close64( fd );
  return res;
}
#endif


#ifdef HAVE_READ64
ssize_t read64(int fd, void *buf, size_t count)
{
  ssize_t res;

  res = orig_read64( fd, buf, count );
  
  logfile_write( "read64: fd=%i req=%i read=%i", fd, count, res ); 
  file_stat_read64( fd, res );

  return res;
}
#endif


#ifdef HAVE_WRITE64
ssize_t write64(int fd, const void *buf, size_t count)
{
  ssize_t res;

  res = orig_write64( fd, buf, count );

  logfile_write( "write64: fd=%i req=%i read=%i", fd, count, res ); 
  file_stat_write64( fd, res );

  return res;
}
#endif



/* fopen/fclose/fread/fwrite overloading functions */

FILE *fopen ( const char *filename,
	      const char *mode) 
{
  FILE *file;

  /* do some sanity checks */
  if ( orig_fopen == NULL )
    {
      printf( "Preinit function fopen called (filename=%s)!\n", filename );
      orig_fopen = dlsym( RTLD_NEXT, "fopen" );
      return orig_fopen( filename, mode );
    }

  file = orig_fopen( filename, mode );
  if ( file != NULL )
    {
      logfile_write( "fopen: filename='%s' mode='%s' result=OK", filename, mode );
      file_stat_fopen( filename, file );
    }
  else
    {
      logfile_write( "fopen: filename='%s' mode='%s' result=FAIL", filename, mode );
    }

  return file;
}


int fclose( FILE *file )
{
  int res;

  char *s;

  /* do some sanity checks */
  if ( orig_fclose == NULL )
    {
      printf( "Preinit function fclose called!\n" );
      orig_fclose = dlsym( RTLD_NEXT, "fclose" );
      return orig_fclose( file );
    }

  res = orig_fclose( file );
  s = fstat_filename_file( file );
  if ( s == NULL )
    logfile_write( "fclose: result=%i filename='NULL'", res );
  else
    logfile_write( "fclose: result=%i filename='%s'", res, s  );
  file_stat_fclose( file );

  return res;
}



size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t res;
  
  res = orig_fread( ptr, size, nmemb, stream );
  logfile_write( "fread: req=%i read=%i", (size*nmemb), res ); 
  file_stat_fread( stream, res );

  return res;
}


size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t res;

  res = orig_fwrite( ptr, size, nmemb, stream );
  logfile_write( "fwrite: req=%i write=%i", (size*nmemb), res ); 
  file_stat_fwrite( stream, res );

  return res;
}


/* fopen64/fclose64/fread64/fwrite64 overloading functions */

#ifdef HAVE_FOPEN64
FILE *fopen64 (const char *filename,
	        const char *mode)
{
  FILE *file;

  /* do some sanity checks */
  /*if ( orig_fopen64 == NULL )
    {
      printf( "Preinit function fopen64 called (filename=%s)!\n", filename );
      orig_fopen64 = dlsym( RTLD_NEXT, "fopen64" );
      return orig_fopen64( filename, mode );
    } */

  if ( orig_fopen64 == NULL )
    return NULL;

  file = orig_fopen64( filename, mode );
  
  if ( file != NULL )
    {
      logfile_write( "fopen64: filename='%s' mode='%s' result=OK", filename, mode );
      file_stat_fopen64( filename, file );
    }
  else
    {
      logfile_write( "fopen64: filename='%s' mode='%s' result=FAIL", filename, mode );
    }


  return file;
}
#endif


#ifdef HAVE_FCLOSE64
int fclose64( FILE *file )
{
  int res;

  /* do some sanity checks */
  if ( orig_fclose64 == NULL )
    return EOF;

  res = orig_fclose64( file );
  logfile_write( "fclose64: result=%i", res );
  file_stat_fclose64( file );

  return res;
}
#endif


#ifdef HAVE_FREAD64
size_t fread64(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t res;

  if ( orig_fread64 == NULL )
    return 0;
  
  res = orig_fread64( ptr, size, nmemb, stream );
  logfile_write( "fread64: req=%i read=%i", (size*nmemb), res ); 
  file_stat_fread64( stream, res );

  return res;
}
#endif


#ifdef HAVE_FWRITE64
size_t fwrite64(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t res;

  if ( orig_fwrite64 == NULL )
    return 0;

  res = orig_fwrite64( ptr, size, nmemb, stream );
  logfile_write( "fwrite64: req=%i write=%i", (size*nmemb), res ); 
  file_stat_fwrite64( stream, res );

  return res;
}
#endif



int printf( const char* format, ... )
{
  int      res;

  va_list  ap;
  void    *arg;
  
  va_start( ap, format );
  arg = va_arg( ap, void * );
  va_end( ap );

  res = orig_printf( format, arg );

  logfile_write2( "printf", format, arg );

  return res;
}



/* special section for the Darwin MacOS $NOCANCEL routines */

#ifdef IS_DARWIN

/* import some basic definitions */
#include "darwin_nocancel.h"

int oopen$NOCANCEL$__interposed__ ( const char *filename, int flag, int  mode )

{
  const int     res = open$NOCANCEL( filename, flag, mode  );


  logfile_write( "open_nocancel: filename='%s' mode=%i (%s) fd=%i", 
		 filename, flag, fstat_flag_str( flag ), res );

   file_stat_open( filename, res );
  return( res );
} 

int open$NOCANCEL$__interposed__ ( const char *filename, int flag, ...)

{
  va_list ap;
  int     res;
  void   *arg;

  va_start( ap, flag );
  arg = va_arg(ap, void *);
  va_end( ap );

  res = open$NOCANCEL( filename, flag, arg );

  logfile_write( "open_nocancel: filename='%s' mode=%i (%s) fd=%i", 
		 filename, flag, fstat_flag_str( flag ), res );

  file_stat_open( filename, res );
  return( res );
} 
#endif


int close$NOCANCEL$__interposed__( int fd )
{
  int res;

  res = close$NOCANCEL( fd );
  logfile_write( "close_nocancel: fd=%i result=%i ", fd, res );
  file_stat_close( fd );
  return res;
}


ssize_t read$NOCANCEL$__interposed__(int fd, void *buf, size_t count)
{
  ssize_t res;

  res = read$NOCANCEL( fd, buf, count );
  
  logfile_write( "read_nocancel: fd=%i req=%i read=%i", fd, count, res ); 
  file_stat_read( fd, res );

  return res;
}


ssize_t write$NOCANCEL$__interposed__(int fd, const void *buf, size_t count)
{
  ssize_t res;

  res = write$NOCANCEL( fd, buf, count );

  logfile_write( "write_nocancel: fd=%i req=%i read=%i", fd, count, res ); 
  file_stat_write( fd, res );

  return res;
}
