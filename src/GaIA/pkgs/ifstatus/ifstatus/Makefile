# Makefile for IFStatus
# Gabriel Montenegro 

GCC = g++
LDFLAGS = -lncurses
CFLAGS = -O2 -Wall

BIN = ifstatus
OBJ = BorderDecorator.o\
	Config.o\
	Curses.o\
	Decorator.o\
	Display.o\
	Email.o\
	Graph.o\
	GraphDecorator.o\
	IFStatus.o\
	Information.o\
	Interface.o\
	Interfaces.o\
	Main.o\
	Util.o\
	Window.o
	

INSTDIR = /usr/local/bin
INSTALL=/usr/bin/install
INSTALL_PARMS=-o 0 -g 0 -s -m 0755

all : ifstatus printdone

ifstatus : $(OBJ)
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $@

printdone:
	@if [ -e "./${BIN}" ]; then echo "Compiled.."; else echo "Error compiling!"; fi

clean:
	rm -f ${BIN} *.o core *~ 
install:
	$(INSTALL) $(INSTALL_PARMS) ifstatus /usr/local/bin



