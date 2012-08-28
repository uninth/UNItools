#include <sys/stat.h>
/* logfile.c

   written: Oliver Cordes 2012-08-01
   updated: Oliver Cordes 2014-06-15

   $Id$

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <errno.h>
#include <time.h>
#include <stdarg.h>

#include <fcntl.h>
#include <unistd.h>

#include "file_stat.h"
#include "myprintf.h"
#include "params.h"


/* NOTE: 

   on MacOS the time function reads /etc/localtime, so the first write of the timestamp inside the logfile 
   produces open/read/close strings which were written before the first timestamo is written to the file, so
   during the init process cache all write commands and overrides the real init writes, then flush the cache. 
   As a result the logging file looks normal again ... and in correct logical order, it may be that the time 
   information maybe differ within one second ... but I didn't see this so far! 
*/



int logging_logfile = -1;

int logging_available = 0;


char last_timestamp[50];

#define max_printf_buffer 512
char *printf_buffer[max_printf_buffer];
int   printf_buffer_len;


void logfile_printf_buffer_flush( int file )
{
  int i;

  for (i=0;i<printf_buffer_len;i++)
    {
      orig_write( file, printf_buffer[i], strlen(  printf_buffer[i] ) );
      free(  printf_buffer[i] );
    }
  printf_buffer_len = 0;
}


void logfile_printf_buffer_add( char * s)
{
  if ( printf_buffer_len < max_printf_buffer )
      printf_buffer[printf_buffer_len++] = strdup( s );
}


void logfile_printf( int file, char *s, int override )
{
  if ( ( logging_available == 1 ) || ( override == 1 ) )
    {
      /* rewind to end, if someone cut the file for saving operations */
      lseek( file, 0, SEEK_END );
      orig_write( file,  s, strlen( s ) );
    }
  else
    logfile_printf_buffer_add( s );
}


void write_timestamp ( int file, int override )
{
  static struct tm    timep;
  static time_t       times;

  static char last_timestamp[50];
  
  times = time( NULL );
  localtime_r( &times, &timep );
  
  
  my_sprintf( last_timestamp, "%02i.%02i.%i %02i:%02i.%02i ", timep.tm_mday,
	  timep.tm_mon+1, timep.tm_year+1900, timep.tm_hour,
	  timep.tm_min, timep.tm_sec );
  logfile_printf( file, last_timestamp, override );
}


void logfile_init ( void )
{

  if ( iostat_logging_name != NULL )
    {
      if ( iostat_trunc_logfile == 1 )
	logging_logfile = orig_open( iostat_logging_name, O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR| S_IRGRP|S_IROTH );
      else
	logging_logfile = orig_open( iostat_logging_name, O_CREAT|O_RDWR|O_APPEND, S_IRUSR|S_IWUSR| S_IRGRP|S_IROTH );
      if ( logging_logfile != -1 )
	{
	  logfile_printf( logging_logfile,
			  "-------------------------------------------------------------------------------\nlogfile opened at: ", 1);
	  write_timestamp( logging_logfile, 1 );
	  logfile_printf( logging_logfile, "\n", 1 ); 

	  /* enable logging */
	  logfile_printf_buffer_flush( logging_logfile );
	  logging_available = 1;
	}
    }
}


void logfile_done ( void )
{
  int file;

  if ( logging_logfile != -1 )
    {
      file = logging_logfile;
      /* switch off logging */
      logging_logfile = -1; 

      logfile_printf( file,  "logfile closed at: ", 0 );
      write_timestamp( file, 0 );
      logfile_printf( file,
		      "\n-------------------------------------------------------------------------------\n", 0
	       ); 
      orig_close( file ); 
      } 
}


void logfile_write( char *format, ... )
{
    char dummy[1000];

    va_list ap;

    if ( logging_logfile != -1 )
      {
	va_start( ap, format );
	//vsnprintf( dummy, 1000, format, ap );
	my_vsprintf( dummy, format, ap );
	va_end( ap );


	write_timestamp( logging_logfile, 0 );
	logfile_printf( logging_logfile, dummy, 0 );
	logfile_printf( logging_logfile, "\n", 0 );
      }

}


void logfile_write2( char *msg, const char *format, ... )
{
    char dummy[1000];

    va_list ap;

    if ( logging_logfile != -1 )
      {
	va_start( ap, format );
	vsnprintf( dummy, 1000, format, ap );
	va_end( ap );

	write_timestamp( logging_logfile, 0);
	logfile_printf( logging_logfile, msg, 0 );
	logfile_printf( logging_logfile, ": ", 0 );
	logfile_printf( logging_logfile, dummy, 0 );
	logfile_printf( logging_logfile, "\n", 0 );
      }
}
