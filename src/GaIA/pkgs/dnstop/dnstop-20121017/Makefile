PROG=dnstop

OPTFLAGS= -DUSE_IPV6=1
CC=gcc
CFLAGS=-g -O2 ${OPTFLAGS}
LIBS=-lresolv -lnsl -lpcap -lncurses 
LDFLAGS=-static

prefix=/var/opt/UNItools
exec_prefix=${prefix}
bindir=/var/opt/UNItools/bin
datarootdir=${prefix}/share
datadir=${datarootdir}
mandir=/var/opt/UNItools/share/man

SRCS=	$(PROG).c \
	hashtbl.c hashtbl.h \
	inX_addr.c inX_addr.h \
	known_tlds.h \
	lookup3.c

OBJS=	$(PROG).o \
	hashtbl.o \
	inX_addr.o \
	lookup3.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) ${LIBS}

clean:
	rm -f $(PROG) $(OBJS) $(PROG).core $(PROG).c~

distclean: clean
	rm -rf autom4te.cache
	rm -f config.h
	rm -f config.log
	rm -f config.status
	rm -f config.status.lineno
	rm -f Makefile

tar:
	DATE=`date +%Y%m%d` && \
	mkdir $(PROG)-$$DATE && \
	cp -p LICENSE CHANGES $(SRCS) $(PROG).8 $(PROG)-$$DATE && \
	cp -p configure Makefile.in config.h.in install-sh $(PROG)-$$DATE && \
	cp -p configure.scan $(PROG)-$$DATE/configure.ac && \
	perl -pi -e "s/\@VERSION\@/$$DATE/" $(PROG)-$$DATE/dnstop.c && \
	tar czvf $(PROG)-$$DATE.tar.gz $(PROG)-$$DATE && \
	chmod 444 $(PROG)-$$DATE.tar.gz && \
	rm -rf $(PROG)-$$DATE && \
	md5 *.gz > MD5s.txt

install: $(PROG)
	install -m 755 $(PROG) ${DESTDIR}${bindir}
	install -m 644 $(PROG).8 ${DESTDIR}${mandir}/man8

uninstall:
	rm -f ${DESTDIR}${bindir}/$(PROG)
	rm -f ${DESTDIR}${mandir}/man8/$(PROG).8
