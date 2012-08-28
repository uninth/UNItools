#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/conf_template/conf_template.1.0/RCS/Makefile,v 1.4 2014/05/13 21:54:23 root Exp $
#

SCRIPTS		= .bash_profile UNIprofile smtpclient.SH ntp.conf

PREFIX		= /var/opt/UNItools/conf

INSTALL		= /usr/local/bin/install-sh

install:
	test -d $(PREFIX) || mkdir $(PREFIX)
	$(MAKE) conf
	
conf:	$(SCRIPTS)
	for SCRIPT in $(SCRIPTS); do						\
		$(INSTALL) -c -m 0555 -o root -g root $$SCRIPT $(PREFIX);	\
	done
	/bin/rm -f *.bak

.IGNORE:
.SILENT:
.DEFAULT:
	co $<

:

