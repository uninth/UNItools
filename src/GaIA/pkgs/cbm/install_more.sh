#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for cbm
. /home/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/cbm/CFG

# Preserve CWD
SAVEDIR=/home/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/cbm

# Source til cbm ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo cbm 
file $SRC
file $INSTALL_ROOT

exit 0

