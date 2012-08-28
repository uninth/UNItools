#! /bin/sh
#
# Test script for nipper
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/nipper/nipper.0.11.5.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/nipper.0.11.5/nipper.pdf
/bin/rm -f /var/opt/UNItools/docs/nipper.0.11.5/LICENSE
/bin/rm -f /var/opt/UNItools/docs/nipper.0.11.5/Readme
/bin/rm -f /var/opt/UNItools/docs/nipper.0.11.5/Changelog
/bin/rm -f /var/opt/UNItools/docs/nipper.0.11.5/nipper.html
/bin/rm -f /var/opt/UNItools/docs/nipper.0.11.5/nipper.txt
/bin/rm -f /var/opt/UNItools/etc/nipper.conf
/bin/rm -f /var/opt/UNItools/bin/run_nipper_audit.sh
/bin/rm -f /var/opt/UNItools/bin/nipper
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/nipper.0.11.5/nipper.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nipper.0.11.5/nipper.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nipper.0.11.5/LICENSE ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nipper.0.11.5/LICENSE exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nipper.0.11.5/Readme ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nipper.0.11.5/Readme exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nipper.0.11.5/Changelog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nipper.0.11.5/Changelog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nipper.0.11.5/nipper.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nipper.0.11.5/nipper.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/nipper.0.11.5/nipper.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/nipper.0.11.5/nipper.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/etc/nipper.conf ]; then
	echo "ERROR: file /var/opt/UNItools/etc/nipper.conf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/run_nipper_audit.sh ]; then
	echo "ERROR: file /var/opt/UNItools/bin/run_nipper_audit.sh exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/nipper ]; then
	echo "ERROR: file /var/opt/UNItools/bin/nipper exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/nipper
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

