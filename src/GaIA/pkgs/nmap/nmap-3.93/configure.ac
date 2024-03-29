# Require autoconf 2.13 -*- mode: fundamental; -*-
AC_PREREQ(2.13)

dnl Process this file with autoconf to produce a configure script.
AC_INIT(nmap.cc)

AC_ARG_WITH(localdirs,
  [  --with-localdirs        Explicitly ask compiler to use /usr/local/{include,libs} if they exist ],
  [ case "$with_localdirs" in
      yes)
        user_localdirs=1
        ;;
      no)
        user_localdirs=0
        ;;
    esac
    ],
  [ user_localdirs=0 ] )

if test "$user_localdirs" = 1; then
   if test -d /usr/local/lib; then
     LDFLAGS="$LDFLAGS -L/usr/local/lib"
     fi
   if test -d /usr/local/include; then
     CFLAGS="$CFLAGS -I/usr/local/include"
     CXXFLAGS="$CFLAGS -I/usr/local/include"
   fi
fi

libpcapdir=libpcap
AC_SUBST(libpcapdir)

pcredir=libpcre
AC_SUBST(pcredir)

dnl use config.h instead of -D macros
AC_CONFIG_HEADER(config.h)

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
 if test -n "$GXX"; then
      CXXFLAGS="$CXXFLAGS -Wall "
 fi
AC_CHECK_PROG(CXXPROG, "$CXX", "AVAILABLE", "MISSING")
if test $CXXPROG = "MISSING"; then
  AC_MSG_ERROR([Could not locate a C++ compiler. If it exists, add it to your PATH or give configure the CXX=path_to_compiler argument.  Otherwise, install a C++ compiler such as g++ or install a binary package of Nmap (see http://www.insecure.org/nmap/nmap_download.html ))])
fi

nmap_gcc_major_version=0
AC_MSG_CHECKING([whether the compiler is gcc 4 or greater])
if test x"$GXX" = xno; then
  AC_MSG_RESULT([no])
else
  # On some distros, there are snapshots available as gcc4
  if test -z "$ac_cv_prog_CC" || test x"$CC" = xgcc4; then
    our_gcc="$CC"
  else
    our_gcc="$ac_cv_prog_CC"
  fi
  # new major versions must be added here
  case `$our_gcc --version | sed -e 's,\..*,.,' -e q` in
    *4.)
      nmap_gcc_major_version=4
      ;;
    *3.)
      nmap_gcc_major_version=3
      ;;
    *2.)
      nmap_gcc_major_version=2
      ;;
    *1.)
      nmap_gcc_major_version=1
      ;;
  esac
  if test "$nmap_gcc_major_version" -ge 4; then
    AC_MSG_RESULT([yes])
  else
    AC_MSG_RESULT([no])
  fi
fi

# Remember that all following tests will run with this CXXFLAGS by default
if test "$nmap_gcc_major_version" -ge 4; then
  CXXFLAGS="$CXXFLAGS -fno-strict-aliasing"
fi

dnl AC_PROG_INSTALL
dnl AC_PATH_PROG(MAKEDEPEND, makedepend)

dnl Checks for typedefs, structures, and compiler characteristics.

dnl check for void should be put in
dnl AC_MSG_CHECKING(for void)
dnl AC_TRY_COMPILE(, [void *foo = 0;], 
dnl [AC_MSG_RESULT(yes); AC_DEFINE(HAVE_VOID)], [AC_MSG_RESULT(no)])

dnl so should check for 'const'
dnl AC_MSG_CHECKING(for const)
dnl AC_TRY_COMPILE(, [const int foo = 0;], 
dnl [AC_MSG_RESULT(yes); AC_DEFINE(HAVE_CONST)], [AC_MSG_RESULT(no)])

dnl equiv to '#define inline' to 'inline', '__inline__', '__inline' or ''
AC_C_INLINE
if test -n "$sgi_cc"; then
   AC_DEFINE(inline, )
fi

AC_SUBST(COMPAT_OBJS)
AC_SUBST(COMPAT_SRCS)

dnl Host specific hacks
AC_CANONICAL_HOST

linux=no
macosx=no
needs_cpp_precomp=no

case "$host" in
  *alpha-dec-osf*)
    AC_DEFINE(DEC)
    ;;
  *-netbsd* | *-knetbsd*-gnu)
    AC_DEFINE(NETBSD)
    ;;
  *-openbsd*)
    AC_DEFINE(OPENBSD)
    ;;
  *-sgi-irix5*)
    AC_DEFINE(IRIX)
    if test -z "$GCC"; then
      sgi_cc=yes
    fi
    ;;
  *-sgi-irix6*)
    AC_DEFINE(IRIX)
    if test -z "$GCC"; then
      sgi_cc=yes
    fi
    ;;
  *-hpux*)
    AC_DEFINE(HPUX)
    ;;
  *-solaris2.0*)  
    AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG)
    AC_DEFINE(SOLARIS)
    ;;
  *-solaris2.[[1-9]][[0-9]]*)
    AC_DEFINE(SOLARIS)
    ;;
  *-solaris2.1*)
    AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG)
    AC_DEFINE(SOLARIS)
    ;;
  *-solaris2.2*)
    AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG)
    AC_DEFINE(SOLARIS)
    ;;
  *-solaris2.3*)
    AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG)
    AC_DEFINE(SOLARIS)
    ;;
  *-solaris2.4*)
    AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG)
    AC_DEFINE(SOLARIS)
    ;;
  *-solaris2.5.1)
    AC_DEFINE(STUPID_SOLARIS_CHECKSUM_BUG)
    AC_DEFINE(SOLARIS)
    ;;
  *-solaris*)
    AC_DEFINE(SOLARIS)
    ;;
  *-sunos4*)
    AC_DEFINE(SUNOS)
    AC_DEFINE(SPRINTF_RETURNS_STRING)
    ;;
  *-linux*)
    linux=yes
    AC_DEFINE(LINUX)
    AC_DEFINE(PCAP_TIMEOUT_IGNORED)  # libpcap doesn't even LOOK at
                                     # the timeout you give it under Linux
    ;;
  *-freebsd* | *-kfreebsd*-gnu)
    AC_DEFINE(FREEBSD)
    ;;
  *-bsdi*)
    AC_DEFINE(BSDI)
    ;;
  *-apple-darwin*)
    macosx=yes
    AC_DEFINE(MACOSX)
    needs_cpp_precomp=yes
    ;;
esac

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(string.h getopt.h strings.h memory.h sys/param.h sys/sockio.h bstring.h sys/time.h pwd.h unistd.h )
AC_CHECK_HEADERS(netinet/in.h)
AC_CHECK_HEADERS(sys/socket.h)
AC_CHECK_HEADERS([net/if.h],[],[],
[#if HAVE_SYS_TYPES_H
# include <sys/types.h>
# endif
#if HAVE_NETINET_IN_H
# include <netinet/in.h>
# endif
#if HAVE_SYS_SOCKET_H
# include <sys/socket.h>
# endif
])
AC_CHECK_HEADERS([netinet/if_ether.h],[],[],
[#if HAVE_SYS_TYPES_H
# include <sys/types.h>
# endif
#if HAVE_NETINET_IN_H
# include <netinet/in.h>
# endif
# if HAVE_SYS_SOCKET_H
# include <sys/socket.h>
# endif
# if HAVE_NET_IF_H
# include <net/if.h>
# endif
])
AC_HEADER_TIME

dnl Checks for libraries.
dnl AC_CHECK_LIB(m, pow)
dnl on Mac OSX the math library seems to contain unwanted getopt cruft
if test $macosx = no; then
  AC_CHECK_LIB(m, main)
fi

dnl If any socket libraries needed
AC_SEARCH_LIBS(gethostent, nsl)
AC_SEARCH_LIBS(setsockopt, socket)

dnl need posix4/nanosleep for solaris 2.4
AC_SEARCH_LIBS(nanosleep, posix4)

# By default, try to build nmapfe if possible
test "${with_nmapfe+set}" != "set" && with_nmapfe=yes
 
TARGETNMAPFE=nmapfe/nmapfe
INSTALLNMAPFE=install-nmapfe
AC_ARG_WITH(nmapfe, [  --without-nmapfe    skip nmapfe X-window GUI],
 [  case "$with_nmapfe" in
  no)
    TARGETNMAPFE=""; INSTALLNMAPFE=""
    ;;
  esac]
)
AC_SUBST(TARGETNMAPFE)
AC_SUBST(INSTALLNMAPFE)

# First we test whether they specified openssl desires explicitly
use_openssl="yes"
specialssldir=""

AC_ARG_WITH(openssl,
[  --with-openssl=DIR    Use optional openssl libs and includes from [DIR]/lib/ and [DIR]/include/openssl/)],
[  case "$with_openssl" in
  yes)
    ;;
  no)
    use_openssl="no"
    ;;
  *)
    specialssldir="$with_openssl"
    CXXFLAGS="$CXXFLAGS -I$with_openssl/include"
    LDFLAGS="$LDFLAGS -L$with_openssl/lib"
    ;;
  esac]
)

# If they didn't specify it, we try to find it
if test "$use_openssl" = "yes" -a -z "$specialssldir"; then
  AC_CHECK_HEADER(openssl/ssl.h,,
  [ use_openssl="no"
    AC_MSG_WARN([Failed to find openssl/ssl.h so OpenSSL will not be used. If it is installed you can try the --with-openssl=DIR argument]) ])

 if test "$use_openssl" = "yes"; then
   AC_CHECK_HEADER(openssl/err.h,,
    [ use_openssl="no"
    AC_MSG_WARN([Failed to find openssl/err.h so OpenSSL will not be used. If it is installed you can try the --with-openssl=DIR argument]) ])
 fi

 if test "$use_openssl" = "yes"; then
   AC_CHECK_HEADER(openssl/rand.h,,
    [ use_openssl="no"
    AC_MSG_WARN([Failed to find openssl/rand.h so OpenSSL will not be used. If it is installed you can try the --with-openssl=DIR argument]) ])
 fi

# use_openssl="yes" given explicitly in next 2 rules to avoid adding lib to $LIBS
 if test "$use_openssl" = "yes"; then
   AC_CHECK_LIB(crypto, BIO_int_ctrl,
    [ use_openssl="yes"],
    [ use_openssl="no"
    AC_MSG_WARN([Failed to find libcrypto so OpenSSL will not be used. If it is installed you can try the --with-openssl=DIR argument]) ])
 fi

 if test "$use_openssl" = "yes"; then
   AC_CHECK_LIB(ssl, SSL_new,
    [ use_openssl="yes" ],
    [ use_openssl="no"
    AC_MSG_WARN([Failed to find libssl so OpenSSL will not be used. If it is installed you can try the --with-openssl=DIR argument]) ])
 fi
fi

OPENSSL_LIBS=
if test "$use_openssl" = "yes"; then
  AC_DEFINE(HAVE_OPENSSL)
  OPENSSL_LIBS="-lssl -lcrypto"
fi

AC_SUBST(OPENSSL_LIBS)

dnl Check whether libpcap is already available
have_libpcap=no

# By default, search for pcap library
test "${with_libpcap+set}" != "set" && with_libpcap=yes

AC_ARG_WITH(libpcap,
[  --with-libpcap[=DIR]    Look for pcap in DIR/include and DIR/libs. Specify --with-libpcap=included to always use version included with Nmap],
[  case "$with_libpcap" in
  yes)
    AC_CHECK_HEADER(pcap.h,[
      AC_CHECK_LIB(pcap, pcap_datalink,
      [have_libpcap=yes ])])
    ;;
  included)
    have_libpcap=no
   ;;
  *)
    _cppflags=$CXXFLAGS
    _ldflags=$LDFLAGS

    CXXFLAGS="-I$with_libpcap/include $CXXFLAGS"
    LDFLAGS="-L$with_libpcap/lib $LDFLAGS"

    AC_CHECK_HEADER(pcap.h,[
      AC_CHECK_LIB(pcap, pcap_datalink,
	[have_libpcap=yes
	LIBPCAP_INC=$with_libpcap/include
	LIBPCAP_LIB=$with_libpcap/lib])])

    LDFLAGS=$_ldflags
    CXXFLAGS=$_cppflags
    ;;
  esac]
)

if test $linux = yes; then
  have_libpcap=no
fi

if test $needs_cpp_precomp = yes; then
  CXXFLAGS="-no-cpp-precomp $CXXFLAGS"
fi

if test $have_libpcap = yes; then
  if test "${LIBPCAP_INC+set}" = "set"; then
    _cflags=$CXXFLAGS
    _ldflags=$LDFLAGS

    CXXFLAGS="-I$LIBPCAP_INC $CXXFLAGS"
    LDFLAGS="-L$LIBPCAP_LIB $LDFLAGS"
  fi

  # link with -lpcap for the purposes of this test
  LIBS_OLD="$LIBS"
  LIBS="$LIBS -lpcap"
  AC_MSG_CHECKING(if libpcap version is recent enough)
  AC_TRY_RUN([
#include <stdio.h>
extern char pcap_version[];
int main() {
  int major, minor;
  sscanf(pcap_version,"%d.%d", &major, &minor);
  if (major > 0) 
    exit(0);
  if (minor > 4)
    exit(0);
  if (minor < 4)
    exit(1);
  if (pcap_version[3] > 'a')
    exit(0);
  if (pcap_version[3] == 'a') {
    if(!sscanf(&pcap_version[4], "%d", &minor))
      exit(1);
    if (minor >= 6)
      exit(0);
    else
      exit(1);
  }
  exit(1);
}],
[AC_MSG_RESULT(yes); have_libpcap=yes],
[AC_MSG_RESULT(no); have_libpcap=no],
[AC_MSG_RESULT(no); have_libpcap=no])
LIBS="$LIBS_OLD"
fi


LIBPCAP_LIBS="-lpcap"
if test $have_libpcap = yes; then
  PCAP_DEPENDS=""
  PCAP_CLEAN=""
  PCAP_DIST_CLEAN=""
  AC_DEFINE(HAVE_LIBPCAP)
else
  if test "${LIBPCAP_INC+set}" = "set"; then
    LDFLAGS="-L$libpcapdir $_ldflags"
    CXXFLAGS="$_cflags -I$LIBPCAP_INC"
  else
    LDFLAGS="-L$libpcapdir $LDFLAGS"
    CXXFLAGS="$CXXFLAGS -I$libpcapdir"
  fi
  PCAP_DEPENDS='$(LIBPCAPDIR)/libpcap.a'
  PCAP_CLEAN="pcap_clean"
  PCAP_DIST_CLEAN="pcap_dist_clean"
fi

AC_SUBST(PCAP_DEPENDS)
AC_SUBST(PCAP_CLEAN)
AC_SUBST(PCAP_DIST_CLEAN)
AC_SUBST(LIBPCAP_LIBS)

have_pcre=no
requested_included_pcre=no
LIBPCREDIR=libpcre

# First we test whether they specified libpcre explicitly
AC_ARG_WITH(libpcre,
[  --with-libpcre=DIR    Use an existing (compiled) pcre lib from DIR/include and DIR/lib.  Specify --with-libpcre=included to always use the version included with Nmap],
[  case "$with_libpcre" in
  yes)
    ;;
  included)
    requested_included_pcre=yes
    ;;
  *)
    CXXFLAGS="-I$with_libpcre/include $CXXFLAGS"
    LDFLAGS="-L$with_libpcre/lib $LDFLAGS"
    have_pcre=yes
    ;;
  esac]
)

# If they didn't specify it, we try to find it
if test $have_pcre != yes -a $requested_included_pcre != yes ; then
  AC_CHECK_HEADER(pcre.h,
    AC_CHECK_LIB(pcre, pcre_version, [have_pcre=yes ]),
    [AC_CHECK_HEADERS(pcre/pcre.h, 
      [AC_CHECK_LIB(pcre, pcre_version, [have_pcre=yes])]
    )]
  )
fi

# If we still don't have it, we use our own
if test $have_pcre != yes ; then
  AC_CONFIG_SUBDIRS( libpcre )
  CXXFLAGS="-I$LIBPCREDIR $CXXFLAGS"
  LIBPCRE_LIBS="$LIBPCREDIR/libpcre.a"
  PCRE_DEPENDS="$LIBPCREDIR/libpcre.a"
  PCRE_CLEAN="pcre_clean"
  PCRE_DIST_CLEAN="pcre_dist_clean"
else
  LIBPCRE_LIBS="-lpcre"
  PCRE_DEPENDS=""
  PCRE_CLEAN=""
  PCRE_DIST_CLEAN=""
fi

AC_SUBST(LIBPCRE_LIBS)
AC_SUBST(LIBPCREDIR)
AC_SUBST(PCRE_DEPENDS)
AC_SUBST(PCRE_CLEAN)
AC_SUBST(PCRE_DIST_CLEAN)

have_dnet=no
requested_included_dnet=no
LIBDNETDIR=libdnet-stripped

# First we test whether they specified libdnet explicitly
AC_ARG_WITH(libdnet,
[  --with-libdnet=DIR    Use an existing (compiled) dnet lib from DIR/include and DIR/lib.],
[  case "$with_libdnet" in
  yes)
    ;;
  included)
    ;;
  *)
    CXXFLAGS="-I$with_libdnet/include $CXXFLAGS"
    LDFLAGS="-L$with_libdnet/lib $LDFLAGS"
    have_dnet=yes
    ;;
  esac]
)

# If they didn't provide location, we use the included one
if test $have_dnet != yes ; then
  AC_CONFIG_SUBDIRS( libdnet-stripped )
  CXXFLAGS="-I$LIBDNETDIR/include $CXXFLAGS"
  LIBDNET_LIBS="$LIBDNETDIR/src/.libs/libdnet.a"
  DNET_DEPENDS="$LIBDNETDIR/src/.libs/libdnet.a"
  DNET_CLEAN="dnet_clean"
  DNET_DIST_CLEAN="dnet_dist_clean"
else
  LIBDNET_LIBS="-ldnet"
  DNET_DEPENDS=""
  DNET_CLEAN=""
  DNET_DIST_CLEAN=""
fi

AC_SUBST(LIBDNET_LIBS)
AC_SUBST(LIBDNETDIR)
AC_SUBST(DNET_DEPENDS)
AC_SUBST(DNET_CLEAN)
AC_SUBST(DNET_DIST_CLEAN)

dnl AC_HEADER_TIME

AC_MSG_CHECKING([struct ip])
AC_TRY_COMPILE([#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>],
               [struct ip ip;],
               [AC_MSG_RESULT(yes); bsd_networking=yes],
               [AC_MSG_RESULT(no); bsd_networking=no]);
if test $bsd_networking = yes; then

  AC_DEFINE(BSD_NETWORKING)
  AC_MSG_CHECKING([ip_v in struct ip])
  AC_TRY_COMPILE([#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>],
                 [struct ip ip; ip.ip_v;],
                 [AC_MSG_RESULT(yes); has_bitfields=yes],
                 [AC_MSG_RESULT(no); has_bitfields=no])

  if test $has_bitfields = no; then
    SAVE_CXXFLAGS="$CXXFLAGS"
    CXXFLAGS="-D__STDC__=2"

    AC_MSG_CHECKING([if setting __STDC__=2 gives ip_v])
    AC_TRY_COMPILE([#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>],
                   [struct ip ip; ip.ip_v;],
                   [AC_MSG_RESULT(yes); setting_stdc_helps=yes],
                  [AC_MSG_RESULT(no); setting_stdc_helps=no])

    CXXFLAGS="$SAVE_CXXFLAGS"
    if test $setting_stdc_helps = yes; then
      CXXFLAGS="$CXXFLAGS -D__STDC__=2"
    else
      AC_MSG_RESULT(Can't figure out how to get bitfields - configure failed)
      exit 1
    fi
  fi
fi

AC_SUBST(CXXFLAGS)

dnl This test is from the configure.in of Unix Network Programming second
dnl edition example code by W. Richard Stevens
dnl ##################################################################
dnl Check if sockaddr{} has sa_len member.
dnl
AC_CACHE_CHECK(if sockaddr{} has sa_len member, ac_cv_sockaddr_has_sa_len,
        AC_TRY_COMPILE([
#               include <sys/types.h>
#               include <sys/socket.h>],
                [unsigned int i = sizeof(((struct sockaddr *)0)->sa_len)],
        ac_cv_sockaddr_has_sa_len=yes,
        ac_cv_sockaddr_has_sa_len=no))
if test $ac_cv_sockaddr_has_sa_len = yes ; then
        AC_DEFINE(HAVE_SOCKADDR_SA_LEN)
fi

dnl check endedness
AC_C_BIGENDIAN

AC_MSG_CHECKING([if struct in_addr is a wacky huge structure (some Sun boxes)])

AC_TRY_COMPILE([#include <netinet/in.h>], struct in_addr i; i._S_un._S_addr;, \
              AC_DEFINE(IN_ADDR_DEEPSTRUCT) \
              AC_MSG_RESULT(yes) , \
              AC_TRY_COMPILE([#include <sys/types.h>
#include <netinet/in.h>], struct in_addr i; i.S_un.S_addr;, \
                             AC_DEFINE(IN_ADDR_DEEPSTRUCT) \
                             AC_MSG_RESULT(yes) , \
                             AC_MSG_RESULT(no);))

AC_CACHE_CHECK(if struct icmp exists, ac_cv_struct_icmp_exists,
        AC_TRY_COMPILE([
#               include <sys/types.h>
#               include <sys/param.h>
#               include <netinet/in_systm.h>
#               include <netinet/in.h>               
#               define __USE_BSD
#               define __FAVOR_BSD
#               define __BSD_SOURCE
#               include <netinet/ip.h>
#               include <netinet/ip_icmp.h>],
                [unsigned int i = sizeof(struct icmp)],
        ac_cv_struct_icmp_exists=yes,
        ac_cv_struct_icmp_exists=no))
if test $ac_cv_struct_icmp_exists = yes ; then
        AC_DEFINE(HAVE_STRUCT_ICMP)
fi

AC_CACHE_CHECK(if struct ip exists, ac_cv_struct_ip_exists,
        AC_TRY_COMPILE([
#               include <sys/types.h>
#               include <sys/param.h>
#               include <netinet/in_systm.h>
#               include <netinet/in.h>               
#               define __USE_BSD
#               define __FAVOR_BSD
#               define __BSD_SOURCE
#               include <netinet/ip.h>],
                [unsigned int i = sizeof(struct ip)],
        ac_cv_struct_ip_exists=yes,
        ac_cv_struct_ip_exists=no))
if test $ac_cv_struct_ip_exists = yes ; then
        AC_DEFINE(HAVE_STRUCT_IP)
fi

AC_CACHE_CHECK(if struct ip has ip_sum member, ac_cv_ip_has_ip_sum,
        AC_TRY_COMPILE([
#               include <sys/types.h>
#               include <sys/param.h>
#               include <netinet/in_systm.h>
#               include <netinet/in.h>
#               define __USE_BSD
#               define __FAVOR_BSD
#               define __BSD_SOURCE
#               include <netinet/ip.h>
#               include <netinet/ip_icmp.h>],
                [unsigned int i = sizeof(((struct ip *)0)->ip_sum)],
        ac_cv_ip_has_ip_sum=yes,
        ac_cv_ip_has_ip_sum=no))
if test $ac_cv_ip_has_ip_sum = yes ; then
        AC_DEFINE(HAVE_IP_IP_SUM)
fi


dnl Checks for library functions.
dnl AC_TYPE_SIGNAL
AC_CHECK_FUNCS(bzero memcpy nanosleep strerror \
strcasestr inet_aton getopt_long_only)

AC_LANG_PUSH(C++)
AC_MSG_CHECKING([for usleep])
AC_TRY_LINK([#include <unistd.h>],[usleep (200);],[
  AC_MSG_RESULT(yes)],[
  AC_MSG_RESULT(no)
  AC_MSG_CHECKING([if usleep needs custom prototype])
  AC_TRY_LINK([
#include <unistd.h>

extern "C" int usleep (unsigned int);],[
usleep (200);],[
  AC_MSG_RESULT(yes)
  AC_DEFINE(NEED_USLEEP_PROTO)],
  AC_MSG_RESULT(not found))])
AC_LANG_POP(C++)

AC_LANG_PUSH(C++)
AC_TRY_LINK([#include <stdlib.h>
#include <unistd.h>],[
char buffer[200];
gethostname (buffer, 200);], ,[
  AC_MSG_CHECKING([if gethostname needs custom prototype])
  AC_TRY_LINK([
#include <stdlib.h>
#include <unistd.h>

extern "C" int gethostname (char *, unsigned int);],[
char buffer[200];
gethostname (buffer, 200);],[
  AC_MSG_RESULT(yes)
  AC_DEFINE(NEED_GETHOSTNAME_PROTO)],
  AC_MSG_RESULT(not found))])
AC_LANG_POP(C++)

RECVFROM_ARG6_TYPE

dnl AC_CHECK_FUNCS(gethostname gettimeofday select socket strdup strstr )

AC_ARG_WITH(libnbase,
[  --with-libnbase=DIR     Look for nbase include/libs in DIR],
[  case "$with_libnbase" in
  yes)
    ;;
  *)
    NBASEDIR="$with_libnbase"
    ;;
  esac],
NBASEDIR="nbase"
)

LDFLAGS="$LDFLAGS -L$NBASEDIR"
CXXFLAGS="$CXXFLAGS -I$NBASEDIR"
LIBNBASE_LIBS="-lnbase"

AC_SUBST(NBASEDIR)
AC_SUBST(LIBNBASE_LIBS)

NSOCKDIR="nsock"
AC_ARG_WITH(libnsock,
[  --with-libnsock=DIR     Compile and link to libnsock in DIR],
[  case "$with_nsock" in
  yes)
    ;;
  *)
    NSOCKDIR="$with_nsock"
    ;;
  esac]
)

LDFLAGS="$LDFLAGS -L$NSOCKDIR/src/"
CXXFLAGS="$CXXFLAGS -I$NSOCKDIR/include"
LIBNSOCK_LIBS="-lnsock"

AC_SUBST(NSOCKDIR)
AC_SUBST(LIBNSOCK_LIBS)

nmap_cfg_subdirs="$nmap_cfg_subdirs $NSOCKDIR/src"

dnl I need to configure nmapfe and libpcap here since the user might
dnl have specified special options (such as --prefix )
dnl
dnl But I only have to configure libpcap if I am going to use it

if test $have_libpcap = yes ; then
        nmap_cfg_subdirs="$NBASEDIR $nmap_cfg_subdirs"
else
        nmap_cfg_subdirs="$NBASEDIR $libpcapdir $nmap_cfg_subdirs"
fi


if test "${with_nmapfe}" = "yes"; then
dnl Check for GTK+
AC_PATH_PROG(GTK_CONFIG, gtk-config, no)
AC_MSG_CHECKING(If you have GTK+ installed)
if test "$GTK_CONFIG" = "no" ; then
  AC_MSG_RESULT([no])
  AC_MSG_WARN([Gtk+ has not been installed -> nmapfe will not be made])
else
  GTK_NEEDED_MAJOR=1
  GTK_NEEDED_MINOR=2
  GTK_NEEDED_MICRO=7
  GTK_MINVERSION=$GTK_NEEDED_MAJOR.$GTK_NEEDED_MINOR.$GTK_NEEDED_MICRO
  ver=`gtk-config --version`
  dnl Extract the information.
  major=`echo $ver|sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
  minor=`echo $ver|sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
  micro=`echo $ver|sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
  AC_MSG_RESULT($ver)
  if test $major -lt $GTK_NEEDED_MAJOR -o $major -eq $GTK_NEEDED_MAJOR \
    -a $minor -lt $GTK_NEEDED_MINOR -o $minor -eq $GTK_NEEDED_MINOR \
    -a $micro -lt $GTK_NEEDED_MICRO; then
    AC_MSG_WARN([An old version of GTK+ ($major.$minor.$micro) was found.\n \
                 You need at least version $GTK_MINVERSION.\n Subdir X-windows \
                 will not be made])
  else
    nmap_cfg_subdirs="$nmap_cfg_subdirs nmapfe"
    dnl Maybe also define the flags to compile and link GTK+
    dnl GTK_CXXFLAGS=`gtk-config --cflags`
    dnl GTK_LIBS=`gtk-config --libs`
    dnl AC_SUBST(GTK_CXXFLAGS)
    dnl AC_SUBST(GTK_LIBS)
  fi
fi
fi

dnl all hell broke loose when the variable was named $subdirs
AC_CONFIG_SUBDIRS( $nmap_cfg_subdirs )

dnl Configure libpcap if we need to since a lot of lamers don't
dnl already have it installed ...
dnl if test $have_libpcap = nsadf ; then
dnl    echo "Have libpcap is set to $have_libpcap ";
dnl    asdfasdf sdsdf sfd sdfsd
dnl    AC_CONFIG_SUBDIRS( $libpcapdir )
dnl fi

AC_OUTPUT(Makefile)
# Krad ASCII ART#!#@$!@#$
if test -f docs/leet-nmap-ascii-art.txt; then
	cat docs/leet-nmap-ascii-art.txt
fi
echo "Configuration complete.  Type make (or gmake on some *BSD machines) to compile."
