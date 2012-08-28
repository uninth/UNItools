AC_INIT([iostat], [1.0.0], [ocordes@astro.uni-bonn.de])
AC_CANONICAL_TARGET
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_LIBTOOL
AC_PROG_CC
AC_HEADER_STDC
AC_CONFIG_HEADERS([src/config.h:src/config.in])
AC_CHECK_HEADERS(utime.h)
AC_FUNC_UTIME_NULL
AC_CHECK_FUNCS( open64 close64 read64 write64 )
AC_CHECK_FUNCS( fopen64 fclose64 fread64 fwrite64 )

case "${host_os}" in
  darwin*)
    R_OS_TYPE="darwin"
    AC_DEFINE([IS_DARWIN], [], [host is a MacOS system])
    AC_DEFINE_UNQUOTED(IS_DARWIN, 1)
    ;;
  linux-gnu*)
    AC_DEFINE([IS_LINUX], [], [host is a linux system])
    AC_DEFINE_UNQUOTED(IS_LINUX, 1)
    ;;
esac

AC_CONFIG_FILES([
 Makefile
])
AC_OUTPUT
