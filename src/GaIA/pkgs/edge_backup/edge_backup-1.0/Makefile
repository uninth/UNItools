#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/edge_backup/edge_backup-1.0/Makefile,v 1.2 2014/05/13 21:38:02 root Exp $
#

SCRIPTS		= edge_backup.sh
TEMPLATES	= edge_backup.cfg.template edge_backup.cfg

PREFIX		= /var/opt/UNItools
BINDIR		= $(PREFIX)/bin
ETCDIR		= $(PREFIX)/etc
MANDIR		= $(PREFIX)/share/man/man1

INSTALL		= /usr/local/bin/install-sh
SRCTOMAN	= /usr/local/bin/srctoman

install:
	$(MAKE) bin
	$(MAKE) etc
	$(MAKE) man
	$(MAKE) clean
	
bin:	$(SCRIPTS)
	test -d $(BINDIR) || mkdir -p $(BINDIR);				\
	for SCRIPT in $(SCRIPTS); do						\
		$(INSTALL) -c -m 0555 -o root -g root $$SCRIPT $(BINDIR);	\
	done

etc:	$(TEMPLATES)
	test -d $(ETCDIR) || mkdir -p $(ETCDIR);				\
	for FILE in $(TEMPLATES); do						\
		$(INSTALL) -c -m 0444 -o root -g root $$FILE $(ETCDIR);	\
	done

edge_backup.cfg: edge_backup.cfg.template
	/bin/cp edge_backup.cfg.template edge_backup.cfg

man:	$(SCRIPTS)
	test -d $(MANDIR) || mkdir -p $(MANDIR);				\
	for SCRIPT in $(SCRIPTS); do						\
		$(SRCTOMAN) - $$SCRIPT > $$SCRIPT.1;				\
		$(INSTALL) -c -m 0444 -o root -g root $$SCRIPT.1 $(MANDIR);	\
	done

clean:
	/bin/rm -fr *.bak $(PREFIX)/etc/edge_backup.cfg

.IGNORE:
.SILENT:
.DEFAULT:
	co $<
