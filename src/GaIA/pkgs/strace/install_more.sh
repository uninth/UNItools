#!/bin/sh
#
# This script is executed *after* the ''make install''
# and is intented to polute /var/opt/UNItools with extra files
#

# Source configuration for strace 4.8
. ./CFG

# Preserve CWD
SAVEDIR=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/strace

# Program source is in SRC from CFG
SRC=$SRC

# Install target dir
INSTALL_ROOT=/var/opt/UNItools

echo "Program package: strace"
echo "Program source: $SRC"
echo "My extra stuff should go below $INSTALL_ROOT/doc/strace-4.8"

# Fix interpreter /var/opt/UNItools/bin/strace-graph
sed 's%^#!/usr/bin/perl%#!/var/opt/UNItools/bin/perl%' /var/opt/UNItools/bin/strace-graph > /var/opt/UNItools/bin/strace-graph.tmp
/bin/mv /var/opt/UNItools/bin/strace-graph.tmp /var/opt/UNItools/bin/strace-graph
chmod 555 /var/opt/UNItools/bin/strace-graph

exit 0

