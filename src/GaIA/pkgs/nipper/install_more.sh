#!/bin/sh
#
# This script is executed *after* the ''make install''
# and is intented to polute /var/opt/UNItools with extra files
#

# Source configuration for nipper 0.11.5
. ./CFG

# Preserve CWD
SAVEDIR=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/nipper

# Program source is in SRC from CFG
SRC=$SRC

# Install target dir
INSTALL_ROOT=/var/opt/UNItools

#echo "Program package: nipper"
#echo "Program source: $SRC"
#echo "My extra stuff should go below $INSTALL_ROOT/doc/nipper-0.11.5"

/bin/cp nipper.conf.i2 $INSTALL_ROOT/etc/nipper.conf

cat << 'EOF' > $INSTALL_ROOT/bin/run_nipper_audit.sh
#!/bin/sh
#
#

nipper --fw1 --input=$FWDIR/conf --output=/tmp/nipper-out.tmp
iconv -f latin1 -t utf8 /tmp/nipper-out.tmp > /tmp/`hostname`.html
/bin/rm -f /tmp/nipper-out.tmp

EOF
chmod 755 $INSTALL_ROOT/bin/run_nipper_audit.sh

exit 0

