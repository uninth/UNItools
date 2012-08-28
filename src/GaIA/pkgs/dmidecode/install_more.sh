#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for dmidecode
. /CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til dmidecode ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:

TMPROOT=dmidecode.2.12.install.tmp
/bin/rm -fr $TMPROOT/var/opt/UNItools/share

exit 0

