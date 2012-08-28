#!/bin/sh
#
# This script is executed *after* the ''make install''
# and is intented to polute /var/opt/UNItools with extra files
#

# Source configuration for unbound 1.4.22
. ./CFG

# Preserve CWD
SAVEDIR=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/unbound

# Program source is in SRC from CFG
SRC=$SRC

# Install target dir
INSTALL_ROOT=/var/opt/UNItools

echo "Program package: unbound"
echo "Program source: $SRC"
echo "My extra stuff should go below $INSTALL_ROOT/doc/unbound-1.4.22"

exit 0

