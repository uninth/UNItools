
# written by: Oliver Cordes 2012-07-27
# changed by: Oliver Cordes 2014-06-05
#


AUTOMAKE_OPTIONS = gnu

lib_LTLIBRARIES = libiostat.la

libiostat_la_SOURCES = src/iostat.c \
			src/file_override.c \
			src/file_stat.c \
			src/logfile.c \
			src/myprintf.c \
			src/params.c \
			src/parse.c

include_HEADERS = src/darwin_export.h \
			src/darwin_nocancel.h \
			src/file_stat.h \
			src/logfile.h \
			src/myprintf.h \
			src/params.h \
			src/parse.h

libiostat_la_LIBADD = -ldl
libiostat_la_CFLAGS = -Wall -I src/

# Libtool calls each of those 3 numbers: CURRENT, REVISION, AGE.
# 7:5:1 gives 6.1.5
libiostat_la_LDFLAGS = -version-info 0:1:0

