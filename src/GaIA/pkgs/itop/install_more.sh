#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen
#

. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source
SRC=$SRC

# Temporary install directory
TMPROOT=$SAVEDIR/$PKG.$VER.install.tmp

exit 0

