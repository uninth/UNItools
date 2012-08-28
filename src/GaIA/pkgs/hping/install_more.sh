#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for hping
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til hping ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

DOCDIR=$INSTALL_ROOT/docs/$TOOLBOX_CAT/$PKG.$VER

(
	mkdir -p $DOCDIR
	cd $SRC/docs
	for DOC in APD.txt HPING2-HOWTO.txt HPING2-IS-OPEN MORE-FUN-WITH-IPID SPOOFED_SCAN.txt
	do

	install-sh -c -m 444 -o root $DOC $DOCDIR

	done
)

exit 0

