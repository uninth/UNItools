/* logfile.h

   written: Oliver Cordes 2012-08-01
   updated: Oliver Cordes 2014-06-05

*/


#ifndef __logfile_h
#define __logfile_h 1


void logfile_init ( void );
void logfile_done ( void );

void logfile_write( char *format, ... );
void logfile_write2( char *msg, const char *format, ... );


#endif
