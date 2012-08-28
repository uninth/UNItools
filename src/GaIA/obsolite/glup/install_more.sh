#!/bin/sh
#
# This script is executed *after* the ''make install''
# and is intented to polute /var/opt/UNItools with extra files
#

# Source configuration for glup 1.0
. ./CFG

# Preserve CWD
SAVEDIR=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/glup

# Program source is in SRC from CFG
SRC=$SRC

# Install target dir
INSTALL_ROOT=/var/opt/UNItools

echo "Program package: glup"
echo "Program source: $SRC"
echo "My extra stuff should go below $INSTALL_ROOT/doc/glup-1.0"

exit 0

