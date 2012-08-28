#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for rcs
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til rcs ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo rcs 
file $SRC
file $INSTALL_ROOT

exit 0

