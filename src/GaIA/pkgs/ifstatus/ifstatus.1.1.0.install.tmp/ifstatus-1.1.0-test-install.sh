#! /bin/sh
#
# Test script for ifstatus
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/ifstatus/ifstatus.1.1.0.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/ifstatus.1.1.0/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/ifstatus.1.1.0/README
/bin/rm -f /var/opt/UNItools/docs/ifstatus.1.1.0/COPYING
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/ifstatus.1.1.0/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/ifstatus.1.1.0/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/ifstatus.1.1.0/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/ifstatus.1.1.0/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/ifstatus.1.1.0/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/ifstatus.1.1.0/COPYING exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	
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

