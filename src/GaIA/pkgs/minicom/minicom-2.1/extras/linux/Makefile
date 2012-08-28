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
top_srcdir = ../..

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

top_builddir = ../..

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

EXTRA_DIST = INSTALL README-FIRST mtelnet

AUTOMAKE_OPTIONS = dist-tarZ no-dependencies 1.0
mkinstalldirs = $(SHELL) $(top_srcdir)/aux/mkinstalldirs
CONFIG_HEADER = ../../config.h
CONFIG_CLEAN_FILES = 
DIST_COMMON =  INSTALL Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
all: all-redirect
.SUFFIXES:
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu extras/linux/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status

tags: TAGS
TAGS:


distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = extras/linux

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
all-am: Makefile
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
mostlyclean-am:  mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-generic clean-am

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: tags distdir info-am info dvi-am dvi check check-am \
installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
