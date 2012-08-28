#! /bin/sh
#
# Test script for di
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/di/di.4.9.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/share/locale/de_DE/LC_MESSAGES/di.mo
/bin/rm -f /var/opt/UNItools/share/locale/en_US/LC_MESSAGES/di.mo
/bin/rm -f /var/opt/UNItools/docs/di.4.9/LICENSE.iffe
/bin/rm -f /var/opt/UNItools/docs/di.4.9/LICENSE
/bin/rm -f /var/opt/UNItools/docs/di.4.9/README
/bin/rm -f /var/opt/UNItools/docs/di.4.9/di.html
/bin/rm -f /var/opt/UNItools/docs/di.4.9/di.pdf
/bin/rm -f /var/opt/UNItools/docs/di.4.9/di.txt
/bin/rm -f /var/opt/UNItools/bin/di
/bin/rm -f /var/opt/UNItools/bin/mi
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/share/locale/de_DE/LC_MESSAGES/di.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/de_DE/LC_MESSAGES/di.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/en_US/LC_MESSAGES/di.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/en_US/LC_MESSAGES/di.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/di.4.9/LICENSE.iffe ]; then
	echo "ERROR: file /var/opt/UNItools/docs/di.4.9/LICENSE.iffe exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/di.4.9/LICENSE ]; then
	echo "ERROR: file /var/opt/UNItools/docs/di.4.9/LICENSE exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/di.4.9/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/di.4.9/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/di.4.9/di.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/di.4.9/di.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/di.4.9/di.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/di.4.9/di.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/di.4.9/di.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/di.4.9/di.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/di ]; then
	echo "ERROR: file /var/opt/UNItools/bin/di exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/mi ]; then
	echo "ERROR: file /var/opt/UNItools/bin/mi exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/di
ldd /var/opt/UNItools/bin/mi
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

