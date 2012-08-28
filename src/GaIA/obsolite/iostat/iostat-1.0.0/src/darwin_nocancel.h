/* darwin_nocancel.h

   written by: Oliver Cordes 2014-06-02
   changed by: Oliver Cordes 2014-06-02


*/

#ifndef __darwin_nocancel_h

#define __darwin_nocancel_h 1

int open$NOCANCEL( const char *, int, ...);
int close$NOCANCEL( int);
ssize_t read$NOCANCEL( int, void*, size_t );
ssize_t write$NOCANCEL( int, const void*, size_t );

#endif
