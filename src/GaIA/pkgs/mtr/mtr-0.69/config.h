/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader 2.13.  */

/* Define if you don't have the GTK+ libraries available.  */
#define NO_GTK 1

/* Define if you don't have the curses libraries available.  */
/* #undef NO_CURSES */

/* Define if you don't have the herror() function available.  */
/* #undef NO_HERROR */

/* Define if you don't have the strerror() function available.  */
/* #undef NO_STRERROR */

/*  Define the package name.  ("mtr")  */
#define PACKAGE "mtr"

/*  Define the version string.  */
#define VERSION "0.69"


/* The number of bytes in a unsigned char.  */
#define SIZEOF_UNSIGNED_CHAR 1

/* The number of bytes in a unsigned int.  */
#define SIZEOF_UNSIGNED_INT 4

/* The number of bytes in a unsigned long.  */
#define SIZEOF_UNSIGNED_LONG 4

/* The number of bytes in a unsigned short.  */
#define SIZEOF_UNSIGNED_SHORT 2

/* Define if you have the attron function.  */
#define HAVE_ATTRON 1

/* Define if you have the seteuid function.  */
#define HAVE_SETEUID 1

/* Define if you have the <curses.h> header file.  */
#define HAVE_CURSES_H 1

/* Define if you have the <cursesX.h> header file.  */
/* #undef HAVE_CURSESX_H */

/* Define if you have the <ncurses.h> header file.  */
#define HAVE_NCURSES_H 1

/* Define if you have the <ncurses/curses.h> header file.  */
#define HAVE_NCURSES_CURSES_H 1

/* Define if you have the <sys/types.h> header file.  */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/xti.h> header file.  */
/* #undef HAVE_SYS_XTI_H */

/* Define if you have the bind library (-lbind).  */
/* #undef HAVE_LIBBIND */

/* Define if you have the m library (-lm).  */
#define HAVE_LIBM 1

/* Define if you have the ncurses library (-lncurses).  */
#define HAVE_LIBNCURSES 1

/* Define if you have the nsl library (-lnsl).  */
/* #undef HAVE_LIBNSL */

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */

/* Define if you have the termcap library (-ltermcap).  */
#define HAVE_LIBTERMCAP 1

/* Name of package */
#define PACKAGE "mtr"

/* Version number of package */
#define VERSION "0.69"

/* Define to enable IPv6 */
#define ENABLE_IPV6 


/*  Find the proper type for 8 bits  */
#if SIZEOF_UNSIGNED_CHAR == 1
typedef unsigned char uint8;
#else
#error No 8 bit type
#endif

/*  Find the proper type for 16 bits  */
#if SIZEOF_UNSIGNED_SHORT == 2
typedef unsigned short uint16;
#elif SIZEOF_UNSIGNED_INT == 2
typedef unsigned int uint16;
#elif SIZEOF_UNSIGNED_LONG == 2
typedef unsigned long uint16;
#else
#error No 16 bit type
#endif

/*  Find the proper type for 32 bits  */
#if SIZEOF_UNSIGNED_SHORT == 4
typedef unsigned short uint32;
#elif SIZEOF_UNSIGNED_INT == 4
typedef unsigned int uint32;
#elif SIZEOF_UNSIGNED_LONG == 4
typedef unsigned long uint32;
#else
#error No 32 bit type
#endif
