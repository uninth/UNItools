#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for netperf
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til netperf ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo netperf 
file $SRC
file $INSTALL_ROOT

rm /var/opt/UNItools/docs/netperf.2.4.1/netcpu_pstatnew.c

cp netperf_2.1_manual.pdf $INSTALL_ROOT/docs/$PKG.$VER/


exit 0

