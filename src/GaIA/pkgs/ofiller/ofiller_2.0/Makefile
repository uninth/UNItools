#
# UniC Fake Make
#

PKG	= ofiller
VER	= 2.0
TOOLBOX_CAT = GT

install	= /usr/local/bin/install-sh
BIN	= /var/opt/UNItools/bin/
MAN	= /var/opt/UNItools/man/man1/
DOC	= /var/opt/UNItools/docs/$(TOOLBOX_CAT)/$(PKG).$(VER)
HTML	= $(DOC)/HTML
SMPLS	= $(DOC)/Samples

BINS	= ./Linux/odumper.lin ./Linux/ofiller.lin
DOCS	= ./Doc/Users_Manual.pdf ./README.TXT ./Martin_Hoz.asc ./Linux/README_FOR_LINUX_AND_SPLAT.TXT

install: dirs bin docs
	echo "ofiller/odumper: Object Filler and Object Dumper for Check Point"

dirs:
	for DIR in $(BIN) $(MAN) $(DOC) $(SMPLS) $(HTML);	\
	do 							\
		test -d $$DIR || mkdir -p $$DIR ;		\
	done

bin:
	for B in $(BINS);				\
	do						\
		$(install) -c -m 0555 -o root -g root $$B $(BIN)/`basename $$B .lin`;	\
	done

docs:
	for D in $(DOCS);							\
	do									\
		$(install) -c -m 0444 -o root -g root $$D	$(DOC);		\
	done
	for H in ./HTML/*;							\
	do									\
		$(install) -c -m 0444 -o root -g root $$H	$(HTML);	\
	done
	for S in ./Samples/*;							\
	do									\
		$(install) -c -m 0444 -o root -g root $$S	$(SMPLS);	\
	done
