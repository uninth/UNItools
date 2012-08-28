#!/bin/sh
#
# This script template is executed *after* the ''make install''
# and is intented for add/remove/modify extra files to
# /var/opt/UNItools
#

# Source configuration for fping
. /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/fping/CFG

# Preserve CWD
SAVEDIR=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/fping

# Source til fping ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

echo "/lan/ssi/shared/software/internal/pkg_tools/bin/pkg_setup for fping ... "
echo "My source is in $SRC"
echo "My extra stuff should go below $INSTALL_ROOT/doc/fping-3.9"

exit 0

