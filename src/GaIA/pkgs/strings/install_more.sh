#!/bin/bash
#
# Script der *kan kaldes* efter selve installationen
#

echo "Kalder $0 med argumenter $*"

pwd

. /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/strings/CFG

# Preserve CWD
SAVEDIR=/lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/pkgs/strings

# Source
SRC=$SRC

TARFILE=$SAVEDIR/tmp.tar

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

FILES=`find $INSTALL_ROOT -type f -name '*strings*'	\
	-o -name COPYING				\
	-o -name COPYING.LIB				\
	-o -name NEWS					\
	-o -name README`

echo "---- TIL ARKIV: ------------------------"
echo $FILES
echo "----------------------------------------"

rm -f $TARFILE
tar cvfp $TARFILE $FILES

cd $SAVEDIR

/bin/rm -fr $INSTALL_ROOT; cd / && tar xvfp $TARFILE
mkdir -p /var/opt/UNItools/docs/$PKG.$VER

exit 0

