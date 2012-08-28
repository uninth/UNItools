#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/fwbu/fwbu/RCS/Makefile,v 1.2 2012/07/02 08:11:18 root Exp root $
#

SCRIPTS		= setup.sh UNIcpfwbu.sh
CFGS		= extra_files_for_backup.txt UNIcpfwbu.cfg

PREFIX		= /var/opt/UNItools/fwbu/
MANDIR		= /var/opt/UNItools/share/man/man1
BINDIR		= $(PREFIX)/bin
ETCDIR		= $(PREFIX)/etc
MIGRATE		= $(PREFIX)/upgrade_tools

INSTALL		= /usr/local/bin/install-sh
SRCTOMAN	= /usr/local/bin/srctoman

install:
	$(MAKE) bin
	$(MAKE) etc
	$(MAKE) man
	$(MAKE) migrate
	$(MAKE) clean

migrate:
	echo "Search for 'Management Server migration tools for Gaia' on https://supportcenter.checkpoint.com"
	echo "Unpack in check_point_export_migration_tools (no subdir!)"
	echo "and update check_point_export_migration_tools/VERSION with the version number (e.g. 77.30)"
	mkdir -p $(MIGRATE) >/dev/null 2>&1
	/bin/cp -r check_point_export_migration_tools/* $(MIGRATE)

bin:	$(SCRIPTS)
	test -d $(BINDIR) || mkdir -p $(BINDIR);				\
	for SCRIPT in $(SCRIPTS); do						\
		$(INSTALL) -c -m 0555 -o root -g root $$SCRIPT $(BINDIR);	\
	done

etc:	$(CFGS)
	test -d $(ETCDIR) || mkdir -p $(ETCDIR);				\
	for CFG in $(CFGS); do						\
		$(INSTALL) -c -m 0744 -o root -g root $$CFG $(ETCDIR);	\
	done

man:	$(SCRIPTS)
	test -d $(MANDIR) || mkdir -p $(MANDIR);				\
	for SCRIPT in UNIcpfwbu.sh; do						\
		$(SRCTOMAN) - $$SCRIPT > $$SCRIPT.1;				\
		$(INSTALL) -c -m 0444 -o root -g root $$SCRIPT.1 $(MANDIR);	\
	done

clean:
	/bin/rm -fr *.bak

#.IGNORE:
#.SILENT:
.DEFAULT:
	co $<
