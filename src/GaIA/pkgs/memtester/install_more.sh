#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for memtester
. /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/memtester/CFG

# Preserve CWD
SAVEDIR=/lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/memtester

# Source til memtester ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo memtester 
file $SRC
file $INSTALL_ROOT

exit 0

