#
# This file is part of LFT.
#
# The LFT software provided in this Distribution is
# Copyright 2005 VOSTROM Holdings, Inc.
#
# The full text of our legal notices is contained in the file called
# COPYING, included with this Distribution.

# Directory where LFT will be installed:

prefix=/var/opt/UNItools
exec_prefix=${prefix}
bindir=/var/opt/UNItools/bin
mandir=/var/opt/UNItools/share/man
INSTALL=/usr/bin/install -c
LN=ln -s

# Commands/References

CC=gcc
CFLAGS=-g -O2
LIBS=-lpcap -lnsl -lm -lresolv -lnsl 
LDFLAGS=

CAT=cat
CD=cd
MKDIR=mkdir -p
BUILDTYPE=build
RM=rm -rf
SH=sh
SYSTEM=unix
TOOLS=tools
TOUCH=touch


# Specifics

OBJS=lft.o lft_ifname.o whois.o

all: lft whob

lft: $(OBJS)
	$(CC) -o lft $(OBJS) $(LDFLAGS) $(LIBS) -lm

whob: whois.o
	$(CC) -o whob whois.c -DSTANDALONE $(LDFLAGS) $(LIBS) -lm

install: lft lft.8 whob whob.8
	@echo "Installing LFT and WhoB"
	test -d $(bindir)/. || $(MKDIR) $(bindir)
	$(INSTALL) lft $(bindir)/lft
	$(INSTALL) whob $(bindir)/whob
	@ ( echo chown root $(bindir)/lft && chown root $(bindir)/lft && echo chmod u+s $(bindir)/lft && chmod u+s $(bindir)/lft ) || echo "***" WARNING: could not set $(bindir) suid to root
	test -d $(mandir)/man8/. || $(MKDIR) $(mandir)/man8
	@echo "Installing LFT and WhoB manual pages"
	$(INSTALL) lft.8 $(mandir)/man8/lft.8
	$(INSTALL) whob.8 $(mandir)/man8/whob.8

clean:
	$(RM) *.o core* lft whob *~

distclean:
	$(RM) Makefile acconfig.h config.log config.status

better:
	@echo "Sorry, this is the best I can do."

work:
	@echo "Sorry, I didn't write this.  I'm only a Makefile."

love:
	@echo "What do you think I was doing before you bothered me?"

