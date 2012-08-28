#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for saidar
. /home/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/saidar/CFG

# Preserve CWD
SAVEDIR=/home/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/saidar

# Source til saidar ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo saidar 
file $SRC
file $INSTALL_ROOT

/bin/rm -fr /var/opt/UNItools/include /var/opt/UNItools/lib/libstatgrab /var/opt/UNItools/lib/pkgconfig


exit 0

