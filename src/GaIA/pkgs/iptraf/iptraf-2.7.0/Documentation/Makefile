#
# Makefile for Documentation
#

all:
	cat manual.template | sed -e s/@@version@@/`cat version`/ \
	-e s/@@major@@/`awk -F '.' -f version.awk  < version`/ \
	> manual.sgml
	docbook2html manual.sgml

clean:
	rm -f *~ *.html manual.sgml


