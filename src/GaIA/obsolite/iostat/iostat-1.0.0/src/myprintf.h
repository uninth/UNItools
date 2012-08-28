/* myprintf.h

   written by: Oliver Cordes 2014-06-04
   changed by: Oliver Cordes 2014-06-04

*/

#ifndef __myprintf_h

#define __myprintf_h 1

#include <stdarg.h>

int my_vsprintf( char *str, const char *format, va_list ap );
int my_sprintf( char *str, const char *format, ... );


#endif
