#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for smtpclient
. /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/smtpclient/CFG

# Preserve CWD
SAVEDIR=/lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/smtpclient

# Source til smtpclient ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo smtpclient 
file $SRC
file $INSTALL_ROOT

exit 0

