@echo off
set CFLAGS=-Wall -g -O2
rm -f config.h Makefile config.cache
bash ./configure
make clean
make
