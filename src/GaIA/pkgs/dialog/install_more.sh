#!/bin/sh
#
# Script der *kan kaldes* efter selve installationen og skal
# installere / fjerne / ... ting i /var/opt/UNItools
#

echo=/bin/echo
case ${N}$C in
        "") if $echo "\c" | grep c >/dev/null 2>&1; then
                N='-n'
        else
                C='\c'
        fi ;;
esac

# Source konfiguration for dialog
. ./CFG

# Preserve CWD
SAVEDIR=`pwd`

# Source til dialog ligger her:
SRC=$SRC

# Installer / fjern / ... herunder:
INSTALL_ROOT=/var/opt/UNItools

EXAMPLES=$SRC/samples

SAMPLES_DIR=$INSTALL_ROOT/docs/$PKG.$VER/samples

mkdir -p $SAMPLES_DIR

hl="/usr/local/pkg_tools/highlight/bin/highlight -s vim -l -I "

cd $EXAMPLES
find . -type f | while read FILE
do
	$echo $N " $FILE $C"
	# install-sh -c -m 444 $FILE $SAMPLES_DIR
	$hl -S c -i $FILE -o $SAMPLES_DIR/`basename $FILE`.html
done
echo

cd $SAMPLES_DIR
cat << EOF > .info
TITLE:Example dialog scripts
INFO:This is mainly for internal use by UNI-C
EOF

/bin/rm -f index.html && simpleindex.sh

exit 0

