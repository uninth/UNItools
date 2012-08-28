#!/bin/sh
#
# This script is executed *after* the ''make install''
# and is intented to polute /var/opt/UNItools with extra files
#

# Source configuration for postfix 3.0.2
. ./CFG

# Preserve CWD
SAVEDIR=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/postfix

# Program source is in SRC from CFG
SRC=$SRC

# Install target dir
INSTALL_ROOT=/var/opt/UNItools

echo "Program package: postfix"
echo "Program source: $SRC"
echo "My extra stuff should go below $INSTALL_ROOT/doc/postfix-3.0.2"

#
# kør på 2525 IKKE på 25
#
test -f /var/opt/UNItools/postfix/etc/master.cf.org || {
    cp /var/opt/UNItools/postfix/etc/msater.cf /var/opt/UNItools/postfix/etc/master.cf.org
}
awk '{
        if ($1 == "smtp" && $2 == "inet") {
                print "2525       inet  n       -       n       -       -       smtpd"
                print "#" $0
        } else {
                print; next
        }

}' /var/opt/UNItools/postfix/etc/master.cf.org > /var/opt/UNItools/postfix/etc/master.cf

cp postfix-start-stop-script $INSTALL_ROOT/doc/postfix-3.0.2

cat << EOF > $INSTALL_ROOT/doc/postfix-3.0.2/INSTALL_START_STOP_SCRIPT

Kopier postfix-start-stop-script til /etc/init.d og udfør

chkconfig --add postfix-start-stop-script

/etc/init.d/postfix-start-stop-script start

EOF

exit 0
