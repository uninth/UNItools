/* file_stat.c

   written by: Oliver Cordes 2012-07-27
   changed by: Oliver Cordes 2014-06-02


*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#include "config.h"
#include "file_stat.h"
#include "logfile.h"
#include "myprintf.h"
#include "params.h" 


/* global variables */

#define max_entries 65536

_fstat_file_info  *fstat_file_info;
int                fstat_file_info_count;
int                fstat_file_info_max;


_fstat_file_open  *fstat_file_open;
int                fstat_file_open_count;
int                fstat_file_open_max;


_fstat_file_fopen *fstat_file_fopen;
int                fstat_file_fopen_count;
int                fstat_file_fopen_max; 


int                fstat_out = -1;

/* hold the original variables */

int     (*orig_open)     (const char *filename, int flag, ...)                      = NULL;
int     (*orig_close)    (int fd)                                                   = NULL;
ssize_t (*orig_read)     (int fd, void *buf, size_t count)                          = NULL;
ssize_t (*orig_write)    (int fd, const void *buf, size_t count)                    = NULL;

FILE*   (*orig_fopen)    (const char *filename, const char *mode)                   = NULL;
int     (*orig_fclose)   ( FILE *file )                                             = NULL;
size_t  (*orig_fread)    (void *ptr, size_t size, size_t nmemb, FILE *stream)       = NULL;
size_t  (*orig_fwrite)   (const void *ptr, size_t size, size_t nmemb, FILE *stream) = NULL;

#ifdef HAVE_OPEN64
int     (*orig_open64)   (const char *filename, int flag, ...)                      = NULL;
#endif
#ifdef HAVE_CLOSE64
int     (*orig_close64)  (int fd)                                                   = NULL;
#endif
#ifdef HAVE_READ64
ssize_t (*orig_read64)   (int fd, void *buf, size_t count)                          = NULL;
#endif
#ifdef HAVE_WRITE64
ssize_t (*orig_write64)  (int fd, const void *buf, size_t count)                    = NULL;
#endif

#ifdef HAVE_FOPEN64
FILE*   (*orig_fopen64)  (const char *filename, const char *mode)                   = NULL;
#endif
#ifdef HAVE_FCLOSE64
int     (*orig_fclose64) ( FILE *file )                                             = NULL;
#endif
#ifdef HAVE_FREAD64
size_t  (*orig_fread64)  (void *ptr, size_t size, size_t nmemb, FILE *stream)       = NULL;
#endif
#ifdef HAVE_FWRITE64
size_t  (*orig_fwrite64) (const void *ptr, size_t size, size_t nmemb, FILE *stream) = NULL;
#endif


int     (*orig_printf)   (const char *format, ... )                                 = NULL;




/* database functions */

void file_stat_printf( char *format, ... )
{
  char dummy[1000];

  va_list ap;

  if ( fstat_out != -1 )
    {
      va_start( ap, format );
      my_vsprintf( dummy, format, ap );
      va_end( ap );

      orig_write( fstat_out, dummy, strlen( dummy) );
    }
}


void file_stat_print_statistics( void )
{
  int c;

  struct tm    timep;
  time_t       times;
  char         timestamp[50];
  
  times = time( NULL );
  localtime_r( &times, &timep );

  snprintf( timestamp, 50, "%i-%02i-%02i %02i:%02i.%02i ", 
	    timep.tm_year+1900,
	    timep.tm_mon+1,
	    timep.tm_mday,
	    timep.tm_hour,
	    timep.tm_min, timep.tm_sec );


  file_stat_printf( "IO Statistics (%s):\n", timestamp );
  file_stat_printf(
	   "%-40s %10s %10s", 
	   "Filename", 
	   "READS", 
	   "WRITES" );
  #ifdef HAVE_RW64
  file_stat_printf(
	   " %10s %10s",
	   "READS64",
	   "WRITES64" );
  #endif
  #ifdef HAVE_O64
  file_stat_printf(
	   " %6s %6s\n",
	   "OPEN", 
	   "OPEN64" );
  #else
  file_stat_printf(
	   " %3s\n",
	   "OPEN" );
  #endif

  for(c=0;c<fstat_file_info_count;c++)
    {
      file_stat_printf(
	       "%-40s %10llu %10llu",
	       fstat_file_info[c].filename,
	       fstat_file_info[c].reads,
	       fstat_file_info[c].writes );
      #ifdef HAVE_RW64
      file_stat_printf( 
	       " %10llu %10llu",
	       fstat_file_info[c].reads64,
	       fstat_file_info[c].writes64 );
      #endif
      #ifdef HAVE_O64
      file_stat_printf( 
	       " %3i %3i\n",
	       fstat_file_info[c].open,
	       fstat_file_info[c].open64 ); 
      #else
      file_stat_printf( 
	       " %3i\n",
	       fstat_file_info[c].open );
      #endif
    }
}


void file_stat_print_statistic( int c )
{
  #if defined(HAVE_READ64) &&  defined(HAVE_WRITE64) && defined(HAVE_OPEN64)
  file_stat_printf( 
	   "%-40s %10s %10s %10s %10s %3s %3s\n", 
	   "Filename", 
	   "READS", 
	   "WRITES", 
	   "READS64",
	   "WRITES64", 
	   "OPEN", 
	   "OPEN64" );
  file_stat_printf( 
	   "%-40s %10llu %10llu %10llu %10llu %3i %3i\n", 
	   fstat_file_info[c].filename,
	   fstat_file_info[c].reads,
	   fstat_file_info[c].writes,
	   fstat_file_info[c].reads64,
	   fstat_file_info[c].writes64,
	   fstat_file_info[c].open,
	   fstat_file_info[c].open64 ); 
  #else
  file_stat_printf( 
	   "%-40s %10s %10s %3s\n", 
	   "Filename", 
	   "READS", 
	   "WRITES", 
	   "OPEN" );
  file_stat_printf( 
	   "%-40s %10llu %10llu %3i\n", 
	   fstat_file_info[c].filename,
	   fstat_file_info[c].reads,
	   fstat_file_info[c].writes,
	   fstat_file_info[c].open );
  #endif
}


int file_stat_new_entry( __const char *filename )
{
  int c;

  /*printf( "file_stat_new_entry: %i %i %s\n", fstat_file_info_count, fstat_file_info_max, filename ); fflush( stdout ); */
  if ( fstat_file_info_count == fstat_file_info_max )
    return -1;
  c = fstat_file_info_count;
  /*printf( "file_stat_new_entry: new entry %i\n", c ); */
  fstat_file_info[c].filename = strdup( filename );
  fstat_file_info_count++;
  return c;
}

int file_stat_search_database( __const char *filename )
{
  int c = 0;

  for (c=0;c<fstat_file_info_count;c++)
    if ( strcmp( filename, fstat_file_info[c].filename ) == 0 )
      return c;

  return -1;
}


int fstat_new_fd( void )
{
  int c;

  for(c=0;c<fstat_file_open_max;c++)
    if ( fstat_file_open[c].nonfree == 0 )
      return c;

  return -1;
}


int fstat_new_file( void )
{
  int c;

  for(c=0;c<fstat_file_fopen_max;c++)
    if ( fstat_file_fopen[c].nonfree == 0 )
      return c;

  return -1;
}


/* adds a fd to the list of fds, pointing at e */
int fstat_add_open_fd( int e, int fd )
{
  int c;

  c = fstat_new_fd();
  /*printf( "new free fd field! %i\n", c ); */
  if ( c != -1 )
    {
      /*printf( "fstat_add_open_fd: %i %i\n", c, e ); */
      fstat_file_open[c].nonfree = 1;
      fstat_file_open[c].fileid  = e;
      fstat_file_open[c].fd      = fd;
    }

  return c;
}

int fstat_get_open_fd( int fd )
{
  int c;
  
  for(c=0;c<fstat_file_open_max;c++)
    {
      /*printf( "fstat_get_open_fd: c=%i nonfree=%i fd=%i fileid=%i\n", 
	c, fstat_file_open[c].nonfree, fstat_file_open[c].fd, fstat_file_open[c].fileid ); */
      if ( ( fstat_file_open[c].nonfree == 1 )
	   && ( fstat_file_open[c].fd == fd ) )
	return c;
    }

  return -1;
}


int fstat_get_open_info_fd( int fd )
{
  int c;

  c = fstat_get_open_fd( fd );
  /*printf( "fstat_get_open_info_fd: %i %i\n", c, fstat_file_open[c].fileid ); */
  if ( c == -1 )
    return -1;
  else
    return fstat_file_open[c].fileid;
}


/* adds a fd to the list of fds, pointing at e */
int fstat_add_open_file( int e, FILE *file )
{
  int c;

  c = fstat_new_file();
  /*printf( "new free file field! %i\n", c );*/
  if ( c != -1 )
    {
      /*printf( "fstat_add_open_file: %i %i\n", c, e );*/
      fstat_file_fopen[c].nonfree = 1;
      fstat_file_fopen[c].fileid  = e;
      fstat_file_fopen[c].file    = file;
    }

  return c;
}

int fstat_get_open_file( FILE *file )
{
  int c;
  
  for(c=0;c<fstat_file_fopen_max;c++)
    if ( ( fstat_file_fopen[c].nonfree == 1 )
	 && ( fstat_file_fopen[c].file == file ) )
      return c;

  return -1;
}


int fstat_get_open_info_file( FILE *file )
{
  int c;

  c = fstat_get_open_file( file );
  if ( c == -1 )
    return -1;
  else
    return fstat_file_fopen[c].fileid;
}


/* lib functions */

void file_stat_init( void )
{
  int flags;

  fstat_file_info = (_fstat_file_info*) malloc( sizeof( _fstat_file_info ) * max_entries );
  fstat_file_info_count = 0;
  fstat_file_info_max = max_entries;

  fstat_file_open = (_fstat_file_open*) malloc( sizeof( _fstat_file_open ) * max_entries );
  fstat_file_open_count = 0;
  fstat_file_open_max = max_entries;

  fstat_file_fopen = (_fstat_file_fopen*) malloc( sizeof( _fstat_file_fopen ) * max_entries );
  fstat_file_fopen_count = 0;
  fstat_file_fopen_max = max_entries;

  fstat_out = -1;
  if ( iostat_statistics_name != NULL )
    {
      if ( iostat_statistics_append == 1 )
	flags = O_CREAT|O_RDWR|O_APPEND;
      else
	flags = O_CREAT|O_RDWR|O_TRUNC;

      if ( orig_open != NULL )
	fstat_out = orig_open( iostat_statistics_name, flags, S_IRUSR|S_IWUSR| S_IRGRP|S_IROTH );
      else
	fstat_out = open( iostat_statistics_name, flags, S_IRUSR|S_IWUSR| S_IRGRP|S_IROTH );
    }
}



void file_stat_done( void )
{
  file_stat_print_statistics();
  fstat_file_info_count = 0;
  if ( fstat_file_info != NULL )
    free( fstat_file_info );
  
  fstat_file_open_count = 0;
  if ( fstat_file_open != NULL )
    free( fstat_file_open );

  fstat_file_fopen_count = 0;
  if ( fstat_file_fopen != NULL )
    free( fstat_file_fopen );

  if ( iostat_statistics_name != NULL )
    {
      if ( orig_close != NULL )
	orig_close( fstat_out );
      else
	close( fstat_out );
      fstat_out = -1;
    }
}




/* overloaded functions */


/* handle stdin, stdout, stderr */

int file_stat_open_stdin( void )
{
  int e;

  e = file_stat_new_entry( "stdin" );
  if ( e != -1 )
    {
      fstat_file_info[e].open = 0;
      fstat_add_open_file( e, stdin );
      fstat_add_open_fd( e, fileno( stdin ) );
    } 

  return e;
}


int file_stat_open_stdout( void )
{
  int e;

  e = file_stat_new_entry( "stdout" );
  if ( e != -1 )
    {
      fstat_file_info[e].open = 0;
      fstat_add_open_file( e, stdout );
      fstat_add_open_fd( e, fileno( stdout ) );
    } 

  return e;
}


int file_stat_open_stderr( void )
{
  int e;

  e = file_stat_new_entry( "stderr" );
  if ( e != -1 )
    {
      fstat_file_info[e].open = 0;
      fstat_add_open_file( e, stderr );
      fstat_add_open_fd( e, fileno( stderr ) );
    } 

  return e;
}


void file_stat_open( const char *filename, int fd )
{
  int e;

  /*printf( "file_stat_open: %s %i\n", (char*)filename, fd );*/

  e = file_stat_search_database( filename );
  /*printf( "search_database: %i\n", e ); */

  if ( e == -1 )
    {
      e = file_stat_new_entry( filename );
      /*printf( "new entry: %i\n", e );*/
    }
  if ( e != -1 )
    {
      fstat_file_info[e].open++;
      fstat_add_open_fd( e, fd );
    }
}


void file_stat_read( int fd, unsigned long long int reads )
{
  int e;

  e = fstat_get_open_info_fd( fd );
  /*printf( "read: %i\n", e ); */
  if ( e == -1 )
    {
      if ( fd == fileno( stdin ) )
	{
	  printf( "stdin detected!\n" );
	  e = file_stat_open_stdin();
	}
    }
  if ( e != -1 )
    fstat_file_info[e].reads += reads;
}


void file_stat_write( int fd, unsigned long long int writes )
{
  int e;

  e = fstat_get_open_info_fd( fd );
  /*printf( "write: %i\n", e );*/
  if ( e == -1 )
    {
      if ( fd == fileno( stdin ) )
	{
	  /*printf( "stdin detected!\n" ); */
	  e = file_stat_open_stdin();
	}
      else
	{
	  if ( fd == fileno( stdout ) )
	    {
	      /*printf( "stdout detected!\n" );*/
	      e = file_stat_open_stdout();
	    }
	  else
	    {
	      if ( fd == fileno( stderr ) )
		{
		  /*printf( "stderr detected!\n" );*/
		  e = file_stat_open_stderr();
		}
	    }
	}
    }
  if ( e != -1 )
    fstat_file_info[e].writes += writes;
}


void file_stat_close( int fd )
{
  int c, e;

  c = fstat_get_open_fd( fd );
  if ( c != -1 )
    {
      e = fstat_file_open[c].fileid;
      /*printf( "file_stat_close: %i %i\n", c, e );*/
      fstat_file_open[c].nonfree = 0;
      if ( iostat_closing_statistics == 1 )
	file_stat_print_statistic( e );
    }
}

/* overloaded functions for open64/read64/write64/close64 */

#ifdef HAVE_OPEN64
void file_stat_open64( const char *filename, int fd )
{
  int e;

  /*printf( "file_stat_open: %s %i\n", (char*)filename, fd );*/

  e = file_stat_search_database( filename );
  if ( e == -1 )
    e = file_stat_new_entry( filename );
  
  if ( e != -1 )
    {
      fstat_file_info[e].open64++;
      fstat_add_open_fd( e, fd );
    }
}
#endif

#ifdef HAVE_READ64
void file_stat_read64( int fd, unsigned long long int reads )
{
  int e;

  e = fstat_get_open_info_fd( fd );
  /*printf( "read64: %i\n", e ); */
  if ( e != -1 )
    {
      fstat_file_info[e].reads += reads;
      fstat_file_info[e].reads64 += reads;
    }
}
#endif

#ifdef HAVE_WRITE64
void file_stat_write64( int fd, unsigned long long int writes )
{
  int e;

  e = fstat_get_open_info_fd( fd );
  /*printf( "write64: %i\n", e );*/
  if ( e != -1 )
    {
      fstat_file_info[e].writes += writes;
      fstat_file_info[e].writes64 += writes;
    }
}
#endif

#ifdef HAVE_CLOSE64
void file_stat_close64( int fd )
{
  int c, e;

  c = fstat_get_open_fd( fd );
  if ( c != -1 )
    {
      e = fstat_file_open[c].fileid;
      /*printf( "file_stat_close64: %i %i\n", c, e );*/
      fstat_file_open[c].nonfree = 0;
      if ( iostat_closing_statistics == 1 )
	file_stat_print_statistic( e );
    }
}
#endif


/* fopen,fwrite, fread, fclose */
void file_stat_fopen( const char *filename, FILE *file)
{
  int e;

  /*printf( "file_stat_fopen: %s\n", (char*)filename );*/

  e = file_stat_search_database( filename );
  /*printf( "search_database: %i\n", e ); */

  if ( e == -1 )
    {
      e = file_stat_new_entry( filename );
      /*printf( "new entry: %i\n", e ); */
    }

  if ( e != -1 )
    {
      fstat_file_info[e].open++;
      fstat_add_open_file( e, file );
    }
}


void file_stat_fclose( FILE *file)
{
  int c, e;

  c = fstat_get_open_file( file );
  if ( c != -1 )
    {
      e = fstat_file_fopen[c].fileid;
      /*printf( "file_stat_fclose: %i %i\n", c, e );*/
      fstat_file_fopen[c].nonfree = 0;
      if ( iostat_closing_statistics == 1 )
	file_stat_print_statistic( e );
    }
}


void file_stat_fread( FILE *file, unsigned long long int reads )
{
  int e;

  e = fstat_get_open_info_file( file );
  /*printf( "fread: %i\n", e );*/
  if ( e == -1 )
    {
      if ( file == stdin )
	{
	  printf( "stdin detected!\n" );
	  e = file_stat_open_stdin();
	}
    }

  if ( e != -1 )
    {
      fstat_file_info[e].reads += reads;
    }
}


void file_stat_fwrite( FILE *file, unsigned long long int writes )
{
  int e;

  e = fstat_get_open_info_file( file );
  /* printf( "fwrite: %i\n", e ); */
  if ( e == -1 )
    {
      if ( file == stdout )
	{
	  /*printf( "stdout detected!\n" );*/
	  e = file_stat_open_stdout();
	}
      else
	{
	  if ( file == stderr )
	    {
	      /*printf( "stderr detected!\n" ); */
	      e = file_stat_open_stderr();
	    }
	  else
	    printf( "no stream detected!\n" );
	}
	      
    }
  if ( e != -1 )
    {
      fstat_file_info[e].writes += writes;
    }
}


/* fopen64,fwrite64, fread64, fclose64 */
#ifdef HAVE_FOPEN64
void file_stat_fopen64( const char *filename, FILE *file)
{
  int e;

  /*printf( "file_stat_fopen64: %s\n", (char*)filename );*/

  e = file_stat_search_database( filename );
  /*printf( "search_database: %i\n", e ); */

  if ( e == -1 )
    {
      e = file_stat_new_entry( filename );
      /*printf( "new entry: %i\n", e ); */
    }

  if ( e != -1 )
    {
      fstat_file_info[e].open64++;
      fstat_add_open_file( e, file );
    }
}
#endif


#ifdef HAVE_FCLOSE64
void file_stat_fclose64( FILE *file)
{
  int c, e;

  c = fstat_get_open_file( file );
  if ( c != -1 )
    {
      e = fstat_file_fopen[c].fileid;
      /*printf( "file_stat_fclose64: %i %i\n", c, e );*/
      fstat_file_fopen[c].nonfree = 0;
      file_stat_print_statistic( e );
    }
}
#endif

#ifdef HAVE_FREAD64
void file_stat_fread64( FILE *file, unsigned long long int reads )
{
  int e;

  e = fstat_get_open_info_file( file );
  /*printf( "write: %i\n", e );*/
  if ( e == -1 )
    {
      if ( file == stdin )
	{
	  /*printf( "stdin detected!\n" );*/
	  e = file_stat_open_stdin();
	}
    }
  if ( e != -1 )
    {
      fstat_file_info[e].reads += reads;
      fstat_file_info[e].reads64 += reads;
    }
}
#endif


#ifdef HAVE_WRITE64
void file_stat_fwrite64( FILE *file, unsigned long long int writes )
{
  int e;

  e = fstat_get_open_info_file( file );
  /*printf( "write: %i\n", e );*/
  if ( e == -1 )
    {
      if ( file == stdout )
	{
	  /*printf( "stdout detected!\n" ); */
	  e = file_stat_open_stdout();
	}
      else
	{
	  if ( file == stderr )
	    {
	      /*printf( "stderr detected!\n" ); */
	      e = file_stat_open_stderr();
	    }
	}
	      
    }
  if ( e != -1 )
    {
      fstat_file_info[e].writes += writes;
      fstat_file_info[e].writes64 += writes;
    }
}
#endif


char *fstat_filename_file( FILE *file )
{
  static char s[101];
  int e;

  e = fstat_get_open_info_file( file );
  /*printf( "write: %i\n", e );*/
  if ( e != -1 )
    return fstat_file_info[e].filename;
  else
    {
      snprintf( s, 100, "fileno=%i", fileno( file ) );

      return s;
    }
}


/* some flag rountines */


void append_flag( char *s, char *ns )
{
  if ( strlen( s ) != 0 )
    strcat( s, "|" );
  
  strcat( s, ns );
}

char *fstat_flag_str( int flag )
{
  static char aflags[1000];

  aflags[0] = '\0';

  if (  ( flag & O_RDWR ) == O_RDWR )
    {
      append_flag( aflags, "O_WRONLY" );
      flag &= ~O_WRONLY;
    }
  else
    if ( ( flag & O_WRONLY ) == O_WRONLY )
      {
	append_flag( aflags, "O_WRONLY" );
	flag &= ~O_WRONLY;
      }
    else
      if ( ( flag & O_RDONLY ) == O_RDONLY )
	{
	  append_flag( aflags, "O_RDONLY" );
	  flag &= ~O_RDONLY;
	}

  if ( ( flag & O_APPEND ) == O_APPEND )
    {
      append_flag( aflags, "O_APPEND" );
      flag &= ~O_APPEND;
    }
  if ( ( flag & O_ASYNC ) == O_ASYNC )
    {
      append_flag( aflags, "O_ASYNC" );
      flag &= ~O_ASYNC;
    }
  /*if ( ( flag & O_CLOEXEC ) == O_CLOEXEC )
    {
      append_flag( aflags, "O_CLOEXEC" );
      flag &= ~O_CLOEXEC;
      } */
  /*if ( ( flag & O_CREATE ) == O_CREATE )
    {
      append_flag( aflags, "O_CREATE" );
      flag &= ~O_CREATE;
      } */
  /*if ( ( flag & O_DIRECT ) == O_DIRECT )
    {
      append_flag( aflags, "O_DIRECT" );
      flag &= ~O_DIRECT;
      } */
  /*if ( ( flag & O_DIRECTORY ) == O_DIRECTORY )
    {
      append_flag( aflags, "O_DIRECTORY" );
      flag &= ~O_DIRECTORY;
      } */
  if ( ( flag & O_EXCL ) == O_EXCL )
    {
      append_flag( aflags, "O_EXCL" );
      flag &= ~O_EXCL;
    }
  /*if ( ( flag & O_LARGEFILE ) == O_LARGEFILE )
    {
      append_flag( aflags, "O_LARGEFILE" );
      flag &= ~O_LARGEFILE;
      } */
  /*if ( ( flag & O_NOATIME ) == O_NOATIME )
    {
      append_flag( aflags, "O_NOATIME" );
      flag &= ~O_NOATIME;
      } */
  if ( ( flag & O_NOCTTY ) == O_NOCTTY )
    {
      append_flag( aflags, "O_NOCTTY" );
      flag &= ~O_NOCTTY;
    }
  /*if ( ( flag & O_NOFOLLOW ) == O_NOFOLLOW )
    {
      append_flag( aflags, "O_NOFOLLOW" );
      flag &= ~O_NOFOLLOW;
      } */
  if ( ( flag & O_NONBLOCK ) == O_NONBLOCK )
    {
      append_flag( aflags, "O_NONBLOCK" );
      flag &= ~O_NONBLOCK;
    }
  if ( ( flag & O_SYNC ) == O_SYNC )
    {
      append_flag( aflags, "O_SYNC" );
      flag &= ~O_SYNC;
    }
  if ( ( flag & O_TRUNC ) == O_TRUNC )
    {
      append_flag( aflags, "O_TRUNC" );
      flag &=  ~O_TRUNC;
    }

  return aflags;
}
