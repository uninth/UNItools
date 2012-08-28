#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for lshw
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til lshw ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo lshw 
file $SRC
file $INSTALL_ROOT

DOCDIR=$TMPROOT/var/opt/UNItools/docs/$PKG.$VER
#mkdir -p $DOCDIR        >/dev/null

find $SRC/docs -type f | while read DOCFILE
do
	install -c -m 444 $DOCFILE $DOCDIR
done

exit 0

