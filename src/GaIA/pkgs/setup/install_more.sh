#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for setup
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til setup ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo setup 
file $SRC
file $INSTALL_ROOT

exit 0
