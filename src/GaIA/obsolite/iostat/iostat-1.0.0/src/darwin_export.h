/* darwin_export.h

   writtem by: Oliver Cordes 2014-06-02
   changed by: Oliver Cordes 2014-06-02

*/

#ifndef __darwin_export_h
#define __dargin_export_h 1


#include "config.h"


#ifdef IS_DARWIN

int open$__interposed__( const char*, int, ... );
int close$__interposed__( int );
ssize_t read$__interposed__( int, void*, size_t );
ssize_t write$__interposed__( int, const void*, size_t );
int open$NOCANCEL$__interposed__( const char*, int, ... );
int close$NOCANCEL$__interposed__( int );
ssize_t read$NOCANCEL$__interposed__( int, void*, size_t );
ssize_t write$NOCANCEL$__interposed__( int, const void*, size_t );
#endif


#endif
