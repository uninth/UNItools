# Makefile.in generated automatically by automake 1.5 from Makefile.am.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001
# Free Software Foundation, Inc.
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
pkgdatadir = $(datadir)/tcpstat
pkglibdir = $(libdir)/tcpstat
pkgincludedir = $(includedir)/tcpstat
top_builddir = ..

ACLOCAL = ${SHELL} /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/tcpstat/tcpstat-1.5/missing --run aclocal
AUTOCONF = ${SHELL} /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/tcpstat/tcpstat-1.5/missing --run autoconf
AUTOMAKE = ${SHELL} /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/tcpstat/tcpstat-1.5/missing --run automake
AUTOHEADER = ${SHELL} /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/tcpstat/tcpstat-1.5/missing --run autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
INSTALL_HEADER = $(INSTALL_DATA)
transform = s,x,x,
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
AMTAR = ${SHELL} /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/tcpstat/tcpstat-1.5/missing --run tar
AWK = gawk
CC = gcc
DEPDIR = .deps
EXEEXT = 
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
LD_TCPPROF = 
MATHLIB = -lm
OBJEXT = o
PACKAGE = tcpstat
RANLIB = ranlib
TCPPROF = 
VERSION = 1.5
am__include = include
am__quote = 
install_sh = /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/tcpstat/tcpstat-1.5/install-sh

AUTOMAKE_OPTIONS = foreign no-dependencies
noinst_LIBRARIES = libtcpstat.a

INCLUDES = -I../include

libtcpstat_a_SOURCES = print_packet.c process.c tcpseq.c utils.c
subdir = lib
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/include/config.h
CONFIG_CLEAN_FILES =
LIBRARIES = $(noinst_LIBRARIES)

libtcpstat_a_AR = $(AR) cru
libtcpstat_a_LIBADD =
am_libtcpstat_a_OBJECTS = print_packet.$(OBJEXT) process.$(OBJEXT) \
	tcpseq.$(OBJEXT) utils.$(OBJEXT)
libtcpstat_a_OBJECTS = $(am_libtcpstat_a_OBJECTS)

DEFS = -DHAVE_CONFIG_H
DEFAULT_INCLUDES =  -I. -I$(srcdir) -I$(top_builddir)/include
CPPFLAGS = 
LDFLAGS = -static
LIBS = -lpcap 
depcomp =
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
CFLAGS = -O
DIST_SOURCES = $(libtcpstat_a_SOURCES)
DIST_COMMON = Makefile.am Makefile.in
SOURCES = $(libtcpstat_a_SOURCES)

all: all-am

.SUFFIXES:
.SUFFIXES: .c .o .obj
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.in $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --foreign  lib/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status

AR = ar

clean-noinstLIBRARIES:
	-test -z "$(noinst_LIBRARIES)" || rm -f $(noinst_LIBRARIES)
libtcpstat.a: $(libtcpstat_a_OBJECTS) $(libtcpstat_a_DEPENDENCIES) 
	-rm -f libtcpstat.a
	$(libtcpstat_a_AR) libtcpstat.a $(libtcpstat_a_OBJECTS) $(libtcpstat_a_LIBADD)
	$(RANLIB) libtcpstat.a

mostlyclean-compile:
	-rm -f *.$(OBJEXT) core *.core

distclean-compile:
	-rm -f *.tab.c

.c.o:
	$(COMPILE) -c $<

.c.obj:
	$(COMPILE) -c `cygpath -w $<`
uninstall-info-am:

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || etags $(ETAGS_ARGS) $$tags  $$unique $(LISP)

GTAGS:
	here=`CDPATH=: && cd $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH

DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  if test -f $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    $(mkinstalldirs) "$(distdir)/$$dir"; \
	  fi; \
	  if test -d $$d/$$file; then \
	    cp -pR $$d/$$file $(distdir) \
	    || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile $(LIBRARIES)

installdirs:

install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic clean-noinstLIBRARIES mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am:

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic

uninstall-am: uninstall-info-am

.PHONY: GTAGS all all-am check check-am clean clean-generic \
	clean-noinstLIBRARIES distclean distclean-compile \
	distclean-generic distclean-tags distdir dvi dvi-am info \
	info-am install install-am install-data install-data-am \
	install-exec install-exec-am install-info install-info-am \
	install-man install-strip installcheck installcheck-am \
	installdirs maintainer-clean maintainer-clean-generic \
	mostlyclean mostlyclean-compile mostlyclean-generic tags \
	uninstall uninstall-am uninstall-info-am

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
