#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for screen
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til screen ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo screen 
file $SRC
file $INSTALL_ROOT

cp $SRC/etc/etcscreenrc $INSTALL_ROOT/etc/etcscreenrc

exit 0
