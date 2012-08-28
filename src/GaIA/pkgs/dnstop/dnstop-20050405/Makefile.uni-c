CFLAGS=-g -Wall -static
PROG=dnstop
DATE != date +%Y%m%d
CC=gcc

SRCS=	$(PROG).c \
	known_tlds.h

# You may need to uncomment this, esp on Solaris
XTRALIBS= # -lnsl -lresolv -lsocket

all: $(PROG)

$(PROG): $(PROG).o
	$(CC) $(CFLAGS) -o $@ $(PROG).o -lpcap -lcurses $(XTRALIBS)

clean:
	rm -f $(PROG) $(PROG).o $(PROG).core $(PROG).c~

tar:
	mkdir $(PROG)-$(DATE)
	cp -p LICENSE CHANGES $(SRCS) dnstop.8 Makefile $(PROG)-$(DATE)
	tar czvf $(PROG)-$(DATE).tar.gz $(PROG)-$(DATE)
	chmod 444 $(PROG)-$(DATE).tar.gz
	rm -rf $(PROG)-$(DATE)
	md5 *.gz > MD5s.txt

man	= /var/opt/UNItools/man/man1

install:
	mkdir -p $(man) >/dev/null 2>&1
	install-sh -c -m 555 -o root dnstop   /var/opt/UNItools/bin
	install-sh -c -m 444 -o root dnstop.8 $(man)
