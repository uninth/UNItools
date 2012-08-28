CC=gcc -Wall

all: itop

itop: itop.c
	$(CC) -o itop itop.c
	strip itop

clean:
	rm -f itop *.o *~

remake: clean all

install: itop
	cp itop /usr/bin
