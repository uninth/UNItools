# Makefile.in generated automatically by automake 1.4-p6 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = ..

prefix = /var/opt/UNItools
exec_prefix = ${prefix}

bindir = /var/opt/UNItools/bin
sbindir = /var/opt/UNItools/bin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = /var/opt/UNItools/share/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/minicom
pkglibdir = $(libdir)/minicom
pkgincludedir = $(includedir)/minicom

top_builddir = ..

ACLOCAL = aclocal-1.4
AUTOCONF = autoconf
AUTOMAKE = automake-1.4
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = 
host_triplet = i686-pc-linux-gnu
BUILD_INCLUDED_LIBINTL = no
CATALOGS =  cs.gmo es.gmo fr.gmo fi.gmo hu.gmo ja.gmo pl.gmo pt_BR.gmo ru.gmo
CATOBJEXT = .gmo
CC = gcc
CPP = gcc -E
DATADIRNAME = share
GENCAT = gencat
GLIBC21 = yes
GMOFILES =  cs.gmo es.gmo fr.gmo fi.gmo hu.gmo ja.gmo pl.gmo pt_BR.gmo ru.gmo
GMSGFMT = /usr/bin/msgfmt
INSTOBJEXT = .mo
INTLBISON = bison
INTLLIBS = 
INTLOBJS = 
INTL_LIBTOOL_SUFFIX_PREFIX = 
KEYSERV = 
LIBICONV = 
LIBOBJS = 
LIBPORT_GETOPT_LONG_DEP = 
MAKEINFO = makeinfo
MKINSTALLDIRS = aux/mkinstalldirs
MSGFMT = /usr/bin/msgfmt
PACKAGE = minicom
PATH_KERMIT = no
POFILES =  cs.po es.po fr.po fi.po hu.po ja.po pl.po pt_BR.po ru.po
POSUB = po
RANLIB = ranlib
U = 
USE_INCLUDED_LIBINTL = no
USE_NLS = yes
VERSION = 2.1

noinst_LIBRARIES = libport.a
noinst_HEADERS = libport.h getopt.h

libport_a_SOURCES = 

libport_a_LIBADD =  

AUTOMAKE_OPTIONS = dist-tarZ no-dependencies 1.0
mkinstalldirs = $(SHELL) $(top_srcdir)/aux/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
LIBRARIES =  $(noinst_LIBRARIES)


DEFS = -DHAVE_CONFIG_H -I. -I$(srcdir) -I..
CPPFLAGS = 
LDFLAGS = 
LIBS =   -lncurses
libport_a_DEPENDENCIES =  
libport_a_OBJECTS = 
AR = ar
CFLAGS = -g -O2
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
HEADERS =  $(noinst_HEADERS)

DIST_COMMON =  Makefile.am Makefile.in error.c error.h getopt.c \
getopt_long.c snprintf.c usleep.c


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
SOURCES = $(libport_a_SOURCES)
OBJECTS = $(libport_a_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu lib/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


mostlyclean-noinstLIBRARIES:

clean-noinstLIBRARIES:
	-test -z "$(noinst_LIBRARIES)" || rm -f $(noinst_LIBRARIES)

distclean-noinstLIBRARIES:

maintainer-clean-noinstLIBRARIES:

.c.o:
	$(COMPILE) -c $<

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

libport.a: $(libport_a_OBJECTS) $(libport_a_DEPENDENCIES)
	-rm -f libport.a
	$(AR) cru libport.a $(libport_a_OBJECTS) $(libport_a_LIBADD)
	$(RANLIB) libport.a

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags -o $$here/TAGS $(ETAGS_ARGS) $$tags  $$unique $(LISP))

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = lib

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am:
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am:
uninstall: uninstall-am
all-am: Makefile $(LIBRARIES) $(HEADERS)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-noinstLIBRARIES mostlyclean-compile \
		mostlyclean-tags mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-noinstLIBRARIES clean-compile clean-tags clean-generic \
		mostlyclean-am

clean: clean-am

distclean-am:  distclean-noinstLIBRARIES distclean-compile \
		distclean-tags distclean-generic clean-am

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-noinstLIBRARIES \
		maintainer-clean-compile maintainer-clean-tags \
		maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: mostlyclean-noinstLIBRARIES distclean-noinstLIBRARIES \
clean-noinstLIBRARIES maintainer-clean-noinstLIBRARIES \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile tags mostlyclean-tags distclean-tags \
clean-tags maintainer-clean-tags distdir info-am info dvi-am dvi check \
check-am installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


# how to pull in getopt.o if we need to build getopt_long.o?
# can anyone tell me how to express that in automake speak, please...
getopt_long.o: getopt.o

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
