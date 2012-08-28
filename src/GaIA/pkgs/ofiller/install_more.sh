#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen
#

. /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/ofiller/CFG

# Preserve CWD
SAVEDIR=/lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/ofiller

# Source
SRC=$SRC

# Temporary install directory
TMPROOT=$SAVEDIR/$PKG.$VER.install.tmp

echo ofiller 
file $SRC
file $TMPROOT

exit 0

