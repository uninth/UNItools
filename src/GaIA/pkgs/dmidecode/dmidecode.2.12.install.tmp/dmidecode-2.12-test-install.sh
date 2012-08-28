#! /bin/sh
#
# Test script for dmidecode
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/dmidecode/dmidecode.2.12.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/share/doc/dmidecode/AUTHORS
/bin/rm -f /var/opt/UNItools/share/doc/dmidecode/README
/bin/rm -f /var/opt/UNItools/share/doc/dmidecode/CHANGELOG
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.pdf
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.txt
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/LICENSE
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/README
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.pdf
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/ownership.txt
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.pdf
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.html
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.html
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.txt
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.html
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/ownership.pdf
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.txt
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/ownership.html
/bin/rm -f /var/opt/UNItools/docs/dmidecode.2.12/CHANGELOG
/bin/rm -f /var/opt/UNItools/bin/vpddecode
/bin/rm -f /var/opt/UNItools/bin/ownership
/bin/rm -f /var/opt/UNItools/bin/dmidecode
/bin/rm -f /var/opt/UNItools/bin/biosdecode
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/share/doc/dmidecode/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/share/doc/dmidecode/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/doc/dmidecode/README ]; then
	echo "ERROR: file /var/opt/UNItools/share/doc/dmidecode/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/doc/dmidecode/CHANGELOG ]; then
	echo "ERROR: file /var/opt/UNItools/share/doc/dmidecode/CHANGELOG exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/LICENSE ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/LICENSE exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/ownership.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/ownership.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/dmidecode.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/vpddecode.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/ownership.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/ownership.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/biosdecode.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/ownership.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/ownership.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/dmidecode.2.12/CHANGELOG ]; then
	echo "ERROR: file /var/opt/UNItools/docs/dmidecode.2.12/CHANGELOG exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/vpddecode ]; then
	echo "ERROR: file /var/opt/UNItools/bin/vpddecode exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/ownership ]; then
	echo "ERROR: file /var/opt/UNItools/bin/ownership exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/dmidecode ]; then
	echo "ERROR: file /var/opt/UNItools/bin/dmidecode exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/biosdecode ]; then
	echo "ERROR: file /var/opt/UNItools/bin/biosdecode exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/vpddecode
ldd /var/opt/UNItools/bin/ownership
ldd /var/opt/UNItools/bin/dmidecode
ldd /var/opt/UNItools/bin/biosdecode
	) | sed '/=>/!d; s/.*=>//; s/(.*//' | while read SHAREDLIB
	do
		echo "$SHAREDLIB ... "
		if [ ! -e $SHAREDLIB ]; then
			echo "ERROR: shared lib $SHAREDLIB not found"
			ERROR=1
		else
			echo "ok"
		fi
	done
	else
		echo "no dynamically linked files found"
	fi
}

################################################################################
# Main
################################################################################

case $1 in
	cleanup)	rmfiles
				exit 0
	;;
	test)		:
	;;
	*)			echo "usage: /usr/local/bin/pkg_conbat cleanup | test"
				exit 0
esac

test_noclobber
case $ERROR in
	0)	echo "no clobber passed ok"
	;;
	*)	echo error: fix the errors first
		exit 1
	;;
esac

(
	echo "installing files ... "
	cd $TMPROOT
	find var -type f| /bin/cpio -pvdVn /
)

echo "testing shared libs ... "
test_shared_libs

echo "Now try executing some of the commands"
echo "Clean up by executing /usr/local/bin/pkg_conbat cleanup"

