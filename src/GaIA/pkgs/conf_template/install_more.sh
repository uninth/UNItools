#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for conf_template
. /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/conf_template/CFG

# Preserve CWD
SAVEDIR=/lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/conf_template

# Source til conf_template ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo conf_template 
file $SRC
file $INSTALL_ROOT

exit 0

