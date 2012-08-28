#
# $Header: /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/realpath/realpath-1.0/RCS/Makefile,v 1.4 2005/11/08 12:38:58 root Exp $
#
# Makefile for realpath
#

SRCROOT	= /lan/ssi/projects/UNItools/Linux/src

PROG	= realpath
SRC	= $(PROG).c
PROGMAN	= $(PROG).1
PDF	= $(PROG).pdf
TXT	= $(PROG).txt

PREFIX	= /var/opt/UNItools
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/share/man/man1

INSTALL	= /usr/local/bin/install-sh
SRCTOMAN= /usr/local/bin/srctoman -c

install: $(PROG)
	for DIR in $(BINDIR) $(MANDIR);			\
	do						\
		test -d $$DIR || mkdir -p $$DIR;	\
	done
	$(SRCTOMAN) -c $(SRC) > $(PROGMAN)
	$(INSTALL) -c -m 0555 -g wheel -o root $(PROG)		$(BINDIR)
	$(INSTALL) -c -m 0444 -g wheel -o root $(PROGMAN)	$(MANDIR)
	$(MAKE) clean

$(PROG): $(SRC)
	$(CC) -static -O $(SRC) -o $(PROG)
	strip $(PROG)


clean:
	/bin/rm -fr *.bak $(PROG) $(PROGMAN)


# .SILENT:
.IGNORE:
.DEFAULT:
	co $<
