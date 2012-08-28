#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for fwbu
. /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/fwbu/CFG

# Preserve CWD
SAVEDIR=/lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/fwbu

# Source til fwbu ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo fwbu 
file $SRC
file $INSTALL_ROOT

exit 0

