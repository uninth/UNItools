#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

# Source konfiguration for dhcpdmon
.  /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/dhcpdmon/CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til dhcpdmon ligger her:
SRC=$SRC

INSTALL_ROOT=/var/opt/UNItools/dhcping

test -d $INSTALL_ROOT || mkdir	$INSTALL_ROOT

/bin/cp	$SAVEDIR/scripts/dhcping/README_dhcpdmon	$INSTALL_ROOT
/bin/cp	$SAVEDIR/scripts/dhcping/dhcpd-monitor.sh	$INSTALL_ROOT
/bin/cp	$SAVEDIR/scripts/dhcping/dhcpdmon		$INSTALL_ROOT
chmod 555 $INSTALL_ROOT/dhcpdmon
chmod 555 $INSTALL_ROOT/dhcpd-monitor.sh


exit 0

