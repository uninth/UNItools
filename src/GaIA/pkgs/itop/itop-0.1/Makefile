CC = gcc -Wall -static

all: itop

itop: src/itop.c
	cd src && $(CC) -o itop itop.c
	cd src && strip itop

clean:
	cd src && rm -f itop *.o *~

install: itop
	/usr/local/bin/install-sh -c -m 555 src/itop /var/opt/UNItools/bin/itop
	/usr/local/bin/srctoman - ../itop.srctoman > /var/opt/UNItools/share/man/man1/itop.1
