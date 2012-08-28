#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/scripts/scripts-1.0/RCS/Makefile,v 1.12 2016/02/02 09:33:20 root Exp root $
#

# SCRIPTS		= tgz cpfw1mailqmon fw1-tool.pl ipcalc.pl ng2ngx-route.sh printiproute printnetcomment
SCRIPTS		= tgz ipcalc.pl printiproute ipcalc.pl cpfw1mailqmon fw1-tool.pl ng2ngx-route.sh tgz fw1-dump.sh printiproute2gaiaclish ipsort

PREFIX		= /var/opt/UNItools
BINDIR		= $(PREFIX)/bin
MANDIR		= $(PREFIX)/share/man/man1

INSTALL		= /usr/local/bin/install-sh
SRCTOMAN	= /usr/local/bin/srctoman

install:
	$(MAKE) bin
	$(MAKE) man
	$(MAKE) clean
	
bin:	$(SCRIPTS)
	test -d $(BINDIR) || mkdir -p $(BINDIR);				\
	for SCRIPT in $(SCRIPTS); do						\
		$(INSTALL) -c -m 0555 -o root -g root $$SCRIPT $(BINDIR);	\
	done

man:	$(SCRIPTS)
	test -d $(MANDIR) || mkdir -p $(MANDIR);				\
	for SCRIPT in $(SCRIPTS); do						\
		$(SRCTOMAN) - $$SCRIPT > $$SCRIPT.1;				\
		$(INSTALL) -c -m 0444 -o root -g root $$SCRIPT.1 $(MANDIR);	\
	done

clean:
	/bin/rm -fr *.bak

.IGNORE:
.SILENT:
.DEFAULT:
	co $<
