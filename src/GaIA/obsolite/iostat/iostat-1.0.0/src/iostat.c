/* iostat.c

   written by: Oliver Cordes 2012-07-27
   changed by: Oliver Cordes 2014-06-09

*/

#define _GNU_SOURCE
#include <time.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>


#include "config.h"
#include "file_stat.h"
#include "logfile.h"
#include "params.h"

#ifdef IS_DARWIN

#include <mach-o/dyld.h>

/* read all new routines */
#include "darwin_export.h"
#include "darwin_nocancel.h"


#include "dyld-interposing.h"

#endif



void copy_orig_function( void **func, char *funcname, void *newfunc )
{
  char *err;

  (*func) = dlsym( RTLD_NEXT, funcname );
  err = dlerror();
  if ( err != NULL )
    {
      printf( "Can't locate function '%s' (msg='%s')! Override ignored!\n", funcname, err );
    }

  /* some checks mostly for Linux systems */
  
  if ( (*func) == newfunc )
    {
      printf( "%s is not in the list of used functions! Disable '%s'!\n", funcname, funcname );
      (*func) = NULL;
    }
}


void __attach(void) __attribute__((constructor));
void __detach(void) __attribute__((destructor));

void __attach(void)
{
#ifdef IS_DARWIN
    DYLD_INTERPOSE(open$__interposed__, open );
    orig_open = &open; 
    DYLD_INTERPOSE(open$NOCANCEL$__interposed__, open$NOCANCEL );
    DYLD_INTERPOSE(close$__interposed__, close );
    orig_close = &close;
    DYLD_INTERPOSE(close$NOCANCEL$__interposed__, close$NOCANCEL );
    DYLD_INTERPOSE(read$__interposed__, read );
    orig_read = &read;
    DYLD_INTERPOSE(read$NOCANCEL$__interposed__, read$NOCANCEL );
    DYLD_INTERPOSE(write$__interposed__, write );
    orig_write = &write;   
    DYLD_INTERPOSE(write$NOCANCEL$__interposed__, write$NOCANCEL );
#else
    copy_orig_function( (void*) &orig_open, "open", &open );
    copy_orig_function( (void*) &orig_close, "close", &close );
    copy_orig_function( (void*) &orig_read, "read", &read );
    copy_orig_function( (void*) &orig_write, "write", &write );
  /* fopen/fclose/fread/fwrite on Darwin is calling the open/close/read/write directly */
    copy_orig_function( (void*) &orig_fopen, "fopen", &fopen );
    copy_orig_function( (void*) &orig_fclose, "fclose", &fclose );
    copy_orig_function( (void*) &orig_fread, "fread", &fread );
    copy_orig_function( (void*) &orig_fwrite, "fwrite", &fwrite );
#endif

  #ifdef HAVE_OPEN64
    copy_orig_function( (void*) &orig_open64, "open64", &open64 );
  #endif
  #ifdef HAVE_CLOSE64
    copy_orig_function( (void*) &orig_close64, "close64", &close64 );
  #endif
  #ifdef HAVE_READ4
    copy_orig_function( (void*) &orig_read64, "read64", &read64 );
  #endif
  #ifdef HAVE_WRITE64
    copy_orig_function( (void*) &orig_write64, "write64", &write64 );
  #endif

  #ifdef HAVE_FOPEN64
    copy_orig_function( (void*) &orig_fopen64, "fopen64", &fopen64 );
  #endif
  #ifdef HAVE_FCLOSE4
    copy_orig_function( (void*) &orig_fclose64, "fclose64", &fclose64 );
  #endif
  #ifdef HAVE_FREAD64
    copy_orig_function( (void*) &orig_fread64, "fread64", &fread64 );
  #endif
  #ifdef HAVE_FWRITE64
    copy_orig_function( (void*) &orig_fwrite64, "fwrite64", &fwrite64 );
  #endif

  copy_orig_function( (void*) &orig_printf, "printf", &printf );

  params_init();  
  logfile_init(); 
  file_stat_init(); 
}

void __detach(void)
{
  file_stat_done();
  logfile_done(); 
  params_done(); 
}  
