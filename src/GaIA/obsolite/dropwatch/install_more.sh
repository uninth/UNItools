#!/bin/sh
#
# This script is executed *after* the ''make install''
# and is intented to polute /var/opt/UNItools with extra files
#

# Source configuration for dropwatch 1.4
. ./CFG

# Preserve CWD
SAVEDIR=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/dropwatch

# Program source is in SRC from CFG
SRC=$SRC

# Install target dir
INSTALL_ROOT=/var/opt/UNItools

echo "Program package: dropwatch"
echo "Program source: $SRC"
echo "My extra stuff should go below $INSTALL_ROOT/doc/dropwatch-1.4"

exit 0

