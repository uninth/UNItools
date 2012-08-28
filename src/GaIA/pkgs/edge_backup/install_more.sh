#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for edge_backup
. /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/edge_backup/CFG

# Preserve CWD
SAVEDIR=/lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/edge_backup

# Source til edge_backup ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo edge_backup 
file $SRC
file $INSTALL_ROOT

exit 0

