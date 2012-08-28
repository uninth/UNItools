#! /bin/sh
#
# Test script for nload
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/nload/nload.0.7.4.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/nload.0.7.4/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/nload.0.7.4/README
/bin/rm -f /var/opt/UNItools/docs/nload.0.7.4/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/nload.0.7.4/NEWS
/bin/rm -f /var/opt/UNItools/docs/nload.0.7.4/COPYING
/bin/rm -f /var/opt/UNItools/bin/nload
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/nload.0.7.4/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nload.0.7.4/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nload.0.7.4/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nload.0.7.4/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nload.0.7.4/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nload.0.7.4/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nload.0.7.4/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nload.0.7.4/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nload.0.7.4/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nload.0.7.4/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/nload ]; then
	echo "ERROR: file /var/opt/UNItools/bin/nload exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/nload
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

