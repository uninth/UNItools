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
AM_INSTALL_PROGRAM_FLAGS = -m 755

INCLUDES = -I../include

bin_PROGRAMS = tcpstat 
EXTRA_PROGRAMS = tcpprof
noinst_PROGRAMS = packetdump catpcap

tcpstat_SOURCES = tcpstat.c
tcpstat_LDADD = ../lib/libtcpstat.a -lm
tcpstat_DEPENDENCIES = ../lib/libtcpstat.a

tcpprof_SOURCES = stats.c tcpprof.c
tcpprof_LDADD = ../lib/libtcpstat.a 
tcpprof_DEPENDENCIES = ../lib/libtcpstat.a

packetdump_SOURCES = dump.c
packetdump_LDADD = ../lib/libtcpstat.a
packetdump_DEPENDENCIES = ../lib/libtcpstat.a

catpcap_SOURCES = catpcap.c
subdir = src
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/include/config.h
CONFIG_CLEAN_FILES =
EXTRA_PROGRAMS = tcpprof$(EXEEXT)
bin_PROGRAMS = tcpstat$(EXEEXT) 
noinst_PROGRAMS = packetdump$(EXEEXT) catpcap$(EXEEXT)
PROGRAMS = $(bin_PROGRAMS) $(noinst_PROGRAMS)

am_catpcap_OBJECTS = catpcap.$(OBJEXT)
catpcap_OBJECTS = $(am_catpcap_OBJECTS)
catpcap_LDADD = $(LDADD)
catpcap_DEPENDENCIES =
catpcap_LDFLAGS =
am_packetdump_OBJECTS = dump.$(OBJEXT)
packetdump_OBJECTS = $(am_packetdump_OBJECTS)
packetdump_LDFLAGS =
am_tcpprof_OBJECTS = stats.$(OBJEXT) tcpprof.$(OBJEXT)
tcpprof_OBJECTS = $(am_tcpprof_OBJECTS)
tcpprof_LDFLAGS =
am_tcpstat_OBJECTS = tcpstat.$(OBJEXT)
tcpstat_OBJECTS = $(am_tcpstat_OBJECTS)
tcpstat_LDFLAGS =

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
DIST_SOURCES = $(catpcap_SOURCES) $(packetdump_SOURCES) \
	$(tcpprof_SOURCES) $(tcpstat_SOURCES)
DIST_COMMON = README Makefile.am Makefile.in
SOURCES = $(catpcap_SOURCES) $(packetdump_SOURCES) $(tcpprof_SOURCES) $(tcpstat_SOURCES)

all: all-am

.SUFFIXES:
.SUFFIXES: .c .o .obj
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.in $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --foreign  src/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  p1=`echo $$p|sed 's/$(EXEEXT)$$//'`; \
	  if test -f $$p \
	  ; then \
	    f=`echo $$p1|sed '$(transform);s/$$/$(EXEEXT)/'`; \
	   echo " $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/$$f"; \
	   $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/$$f; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  f=`echo $$p|sed 's/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/'`; \
	  echo " rm -f $(DESTDIR)$(bindir)/$$f"; \
	  rm -f $(DESTDIR)$(bindir)/$$f; \
	done

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

clean-noinstPROGRAMS:
	-test -z "$(noinst_PROGRAMS)" || rm -f $(noinst_PROGRAMS)
catpcap$(EXEEXT): $(catpcap_OBJECTS) $(catpcap_DEPENDENCIES) 
	@rm -f catpcap$(EXEEXT)
	$(LINK) $(catpcap_LDFLAGS) $(catpcap_OBJECTS) $(catpcap_LDADD) $(LIBS)
packetdump$(EXEEXT): $(packetdump_OBJECTS) $(packetdump_DEPENDENCIES) 
	@rm -f packetdump$(EXEEXT)
	$(LINK) $(packetdump_LDFLAGS) $(packetdump_OBJECTS) $(packetdump_LDADD) $(LIBS)
tcpprof$(EXEEXT): $(tcpprof_OBJECTS) $(tcpprof_DEPENDENCIES) 
	@rm -f tcpprof$(EXEEXT)
	$(LINK) $(tcpprof_LDFLAGS) $(tcpprof_OBJECTS) $(tcpprof_LDADD) $(LIBS)
tcpstat$(EXEEXT): $(tcpstat_OBJECTS) $(tcpstat_DEPENDENCIES) 
	@rm -f tcpstat$(EXEEXT)
	$(LINK) $(tcpstat_LDFLAGS) $(tcpstat_OBJECTS) $(tcpstat_LDADD) $(LIBS)

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
all-am: Makefile $(PROGRAMS)

installdirs:
	$(mkinstalldirs) $(DESTDIR)$(bindir)

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

clean-am: clean-binPROGRAMS clean-generic clean-noinstPROGRAMS \
	mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am:

install-exec-am: install-binPROGRAMS

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic

uninstall-am: uninstall-binPROGRAMS uninstall-info-am

.PHONY: GTAGS all all-am check check-am clean clean-binPROGRAMS \
	clean-generic clean-noinstPROGRAMS distclean distclean-compile \
	distclean-generic distclean-tags distdir dvi dvi-am info \
	info-am install install-am install-binPROGRAMS install-data \
	install-data-am install-exec install-exec-am install-info \
	install-info-am install-man install-strip installcheck \
	installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic tags uninstall uninstall-am \
	uninstall-binPROGRAMS uninstall-info-am

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
