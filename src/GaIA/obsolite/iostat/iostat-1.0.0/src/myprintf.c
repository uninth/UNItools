/* myprintf.c

   written by: Olvier Cordes 2014-06-04
   changed by: Oliver Cordes 2014-06-08

*/

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#include "myprintf.h"


#define version "0.3"

/* history:
   
   2014-06-07: 0.3
   - re-implement %i,%d,%u,%li,%lu,%lli,%llu with format

   2014-06-06: 0.2
   - %s understands now format commands

   2014-06-05: 0.1

   - first version of myprintf
   - supports vsprintf and sprintf
   - supports only %c %s %i
     - for %i +/- and size is implemented
     - for %s no formats are available

*/


const char numeric_char[] = "0123456789abcdef";

char * _copy_string( char *str, char *format, char *arg )
{
  int have_leftformat = 0;
  int have_fillchar   = 0;

  int l, l2 ;

  l = strlen( arg );

  switch( (*format) )
    {
    case '-':
      have_leftformat = 1;
      format++;
      break;
    case '+':
      /*have_plus = 1; */
      format++;
      break;
    case '0':
      have_fillchar = 1;
      format++;
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      /* skip these chars because they belong to length format */
      break;
    default:
      /* skip faulty characters */
      format++;
      break;
    }

  l2 = atoi( format );
  if ( l2 > l  ) 
    l2 -= l;
  else
    l2 = 0;
    
  if ( have_leftformat == 0 )
    {
      while ( l2 > 0 )
	{
	  if ( have_fillchar == 1 )
	    (*str++) = '0';
	  else
	    (*str++) = ' ';
	  l2--;
	}
    }

  while ( (*arg) != '\0' )
    (*str++) = (*arg++);

  if ( have_leftformat == 1 )
    {
      while ( l2 > 0 )
	{
	  (*str++) = ' ';
	  l2--;
	}
    }

  return str;
}


char *_copy_int( char *str, char *format, int64_t arg )
{
  char *dummy;
  char *p;

  int   min_len = 20;
  int   have_plus = 0;
  int   have_leftformat = 0;
  int   have_fillchar = 0;
  int   have_sign = 0;
  
  int   len, l, l2, i;

  if ( arg < 0 )
    {
      have_sign = 1;
      arg = -arg;
    }
  
  dummy = malloc( min_len * sizeof( char ) );

  switch( (*format) )
    {
    case '-':
      have_leftformat = 1;
      format++;
    case '+':
      have_plus = 1;
      format++;
      break;
    default:
      break;
    }

  switch( (*format) )
    {
    case '+':
      have_plus = 1;
      format++;
      break;
    case '0':
      have_fillchar = 1;
      format++;
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      /* skip these chars because they belong to length format */
      break;
    default:
      /* skip faulty characters */
      format++;
      break;
    }

  if ( have_leftformat == 1 )
    have_fillchar = 0;

  if ( have_sign == 1 )
    have_plus = 0;


  len = atoi( format );  /* if format is unknown or NULL then len = 0 */

  if ( len > min_len )
    min_len = len;

  dummy = malloc( min_len * sizeof( char ) );

  l = 0;
  p = dummy;
  do
    {
      i = arg % 10;
      arg /= 10;
      (*p++) = numeric_char[i];
      l++;
    }
  while ( arg > 0 );
  

  if ( have_leftformat == 0 )
    {
      l2 = len;
      if ( ( have_plus == 1 ) || ( have_sign == 1 ) ) l2--;
      while ( l < l2 )
	{
	  if ( have_fillchar == 1 )
	    (*p++) = '0';
	  else
	    (*p++) = ' ';
	  l ++;
	}
    }

  if ( have_sign == 1 )
    {
      (*p++) = '-';
      l++;
    }

  if ( have_plus == 1 ) 
    {
      (*p++) = '+';
      l++;
    }


  len -= l;  /* characters left for spacing */
  /* do the reverse copy */
  while( l >  0 )
    {
      (*str++) = (*--p);
      l--;
    }
  if ( have_leftformat == 1 )
    {
      while ( len > 0 )
	{
	  (*str++) = ' ';
	  len--;
	}
    }
  
  free( dummy );
  return str;
}


char *_copy_unsigned_int( char *str, char *format, uint64_t arg )
{
  char *dummy;
  char *p;

  int   min_len = 20;
  int   have_plus = 0;
  int   have_leftformat = 0;
  int   have_fillchar = 0;
  
  int   len, l, l2, i;

  dummy = malloc( min_len * sizeof( char ) );

  switch( (*format) )
    {
    case '-':
      have_leftformat = 1;
      format++;
    case '+':
      have_plus = 1;
      format++;
      break;
    default:
      break;
    }

  switch( (*format) )
    {
    case '+':
      have_plus = 1;
      format++;
      break;
    case '0':
      have_fillchar = 1;
      format++;
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      /* skip these chars because they belong to length format */
      break;
    default:
      /* skip faulty characters */
      format++;
      break;
    }

  if ( have_leftformat == 1 )
    have_fillchar = 0;

  len = atoi( format );  /* if format is unknown or NULL then len = 0 */

  if ( len > min_len )
    min_len = len;

  dummy = malloc( min_len * sizeof( char ) );

  l = 0;
  p = dummy;
  do
    {
      i = arg % 10;
      arg /= 10;
      (*p++) = numeric_char[i];
      l++;
    }
  while ( arg > 0 );
  

  if ( have_leftformat == 0 )
    {
      l2 = len;
      if ( have_plus == 1 )  l2--;
      while ( l < l2 )
	{
	  if ( have_fillchar == 1 )
	    (*p++) = '0';
	  else
	    (*p++) = ' ';
	  l ++;
	}
    }

 

  if ( have_plus == 1 ) 
    {
      (*p++) = '+';
      l++;
    }


  len -= l;  /* characters left for spacing */
  /* do the reverse copy */
  while( l >  0 )
    {
      (*str++) = (*--p);
      l--;
    }
  if ( have_leftformat == 1 )
    {
      while ( len > 0 )
	{
	  (*str++) = ' ';
	  len--;
	}
    }
  
  free( dummy );
  return str;
}



int my_vsprintf( char *str, const char *format, va_list ap )
{
  char   *cformat;
  char   *inp;
  char   *outp;

  /* data types */
  union{
    void                  *v;
    char                  *s;
    char                   c;
    double                 d;
    int64_t  i;
    uint64_t u;
  } v;

  char   *fmt;

  int     in_loop;

  cformat = strdup( format );
  outp = str;
  inp = (char*) cformat;
  while ( (*inp) != '\0' )
    {
      if ( (*inp) != '%' )
	{
	  (*outp) = (*inp);
	  outp++;
	  inp++;
	}
      else
	{
	  inp++;
	  if ( (*inp) == '\0' )
	    break;
	  else
	    if ( (*inp) == '%' )
	      {
		(*outp) = '%';
		outp++;
		inp++;
		continue;
	      }
	  /* now the complex scanner for replacements */
	  
	  /* find the end of the replacement 
	     ending i,x,s,c,d */
	  fmt = inp;
	  in_loop = 1;
	  do{
	    switch( (*inp) )
	      {
	      case 's':
		(*inp) = '\0';
		v.s = va_arg(ap, char* );
		outp = _copy_string( outp, fmt, v.s );
		in_loop = 0;
		inp++;
		break;
	      case 'c':
		v.c = (char) va_arg(ap, int);
		(*outp++) = v.c;
		in_loop = 0;
		inp++;
		break;
	      case 'd':
	      case 'i':
		(*inp) = '\0';
		v.i = (int64_t) va_arg(ap, int);
		outp = _copy_int( outp, fmt, v.i );
		in_loop = 0;
		inp++;
		break;
	      case 'u':
		(*inp) = '\0';
		v.u = (uint64_t) va_arg(ap, unsigned int);
		outp = _copy_unsigned_int( outp, fmt, v.u );
		in_loop = 0;
		inp++;
		break;
	      case 'e':
	      case 'f':
	      case 'g':
		(*inp) = '\0';
		v.d = va_arg(ap, double);
		in_loop = 0;
		inp++;
		break;
	      case 'x':
		(*inp) = '\0';
		v.i = va_arg(ap, int);
		in_loop = 0;
		inp++;
		break;
	      case 'l':
		inp++;
		switch( (*inp) )
		  {
		  case 'd':
		  case 'i':
		    (*inp) = '\0';
		    v.i = (int64_t) va_arg( ap,int32_t );
		    outp = _copy_int( outp, fmt, v.i );
		    inp++;
		    break;
		  case 'u':
		    (*inp) = '\0';
		    v.i = (uint64_t) va_arg( ap, uint32_t);
		    outp = _copy_unsigned_int( outp, fmt, v.i );
		    inp++;
		    break;
		  case 'l':
		    inp++;
		    switch( inp[0] )
		      {
		      case 'i':
		      case 'd':
			(*inp) = '\0';
			v.i = va_arg( ap, int64_t );
			outp = _copy_int( outp, fmt, v.i );
			inp++;
			break;
		      case 'u':
			(*inp) = '\0';
			v.u = va_arg( ap, uint64_t );
			outp = _copy_unsigned_int( outp, fmt, v.u );
			inp++;
			break;
		      default: 
			/* do nothing */
			break;
		      } /* switch */
		    break;
		  default:  
		    /* do nothing */
		    /* %l  */
		    break;
		  } 
		in_loop = 0;
		break;
	      case '+':
	      case '-':
	      case ' ':
	      case '0':
	      case '1':
	      case '2':
	      case '3':
	      case '4':
	      case '5':
	      case '6':
	      case '7':
	      case '8':
	      case '9':
		inp++;
		break;
	      default:
		/* unknown type, read dummy argument */
		v.v = va_arg( ap, void* );
		inp++;
		break;
	      }
	  } while ( in_loop == 1 );
	}
    } /* scan of the format string */

  free( cformat );
  (*outp) = '\0';
  return strlen( str );
}




int my_sprintf( char *str, const char *format, ... )
{
  va_list ap;
  int     ret;

  va_start( ap, format );
  ret = my_vsprintf( str, format, ap );
  va_end( ap );

  return ret;
}


