#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for host
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til host ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

cd $SRC

mkdir -p $INSTALL_ROOT/man/man1
cp RELEASE_NOTES $INSTALL_ROOT/docs/$PKG.$VER/
cp mxlookup nslookup rblookup $INSTALL_ROOT/bin
cp host.1                     $INSTALL_ROOT/man/man1

exit 0

