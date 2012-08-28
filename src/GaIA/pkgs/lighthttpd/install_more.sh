#!/bin/sh
#
# This script is executed *after* the ''make install''
# and is intented to polute /var/opt/UNItools with extra files
#

# Source configuration for lighthttpd 1.4.39
. ./CFG

# Preserve CWD
SAVEDIR=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/lighthttpd

# Program source is in SRC from CFG
SRC=$SRC

# Install target dir
INSTALL_ROOT=/var/opt/UNItools

echo "Program package: lighthttpd"
echo "Program source: $SRC"
echo "My extra stuff should go below $INSTALL_ROOT/doc/lighthttpd-1.4.39"

exit 0


openssl req 					\
  		-x509					\
		-nodes					\
		-days 10950				\
		-sha512 \
		-subj "/C=DK/ST=Sjaelland/L=Lyngby/CN=`hostname -f`" \
		-newkey rsa:4096		\
		-keyout mycert.pem		\
		-out mycert.pem
exit

openssl req -new -x509 -keyout lighttpd.pem -out lighttpd.pem -days 10950 -nodes
chmod 400 lighttpd.pem
