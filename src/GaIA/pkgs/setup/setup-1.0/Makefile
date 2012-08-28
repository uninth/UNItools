#
# Fake install for setup
#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/setup/setup-1.0/RCS/Makefile,v 1.4 2015/06/25 12:55:27 root Exp $
#

PREFIX	= /var/opt/UNItools/setup

all:
	echo now make install

install:
	/bin/cp -r setup.sh /var/opt/UNItools/bin/
	/bin/cp -r interface_status /var/opt/UNItools/bin
	/bin/cp -r ipropr /var/opt/UNItools/bin
	chmod 555 /var/opt/UNItools/bin/interface_status

distclean:
	echo done
