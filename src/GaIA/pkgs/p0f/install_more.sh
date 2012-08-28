#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen
#

. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source
SRC=$SRC

test -d /var/opt/UNItools/docs/$PKG.$VER/ || mkdir -p /var/opt/UNItools/docs/$PKG.$VER/

cd $SRC
/usr/local/bin/install-sh -c -m 555 p0f		/var/opt/UNItools/bin/
/usr/local/bin/install-sh -c -m 444 p0f.fp	/var/opt/UNItools/etc/

cd tools
for FILE in p0f-client p0f-sendsyn p0f-sendsyn6
do
	/usr/local/bin/install-sh -c -m 555 $FILE	/var/opt/UNItools/bin/
done

/usr/local/bin/install-sh -c -m 444 README-TOOLS /var/opt/UNItools/docs/$TOOLBOX_CAT/$PKG.$VER/

exit 0

