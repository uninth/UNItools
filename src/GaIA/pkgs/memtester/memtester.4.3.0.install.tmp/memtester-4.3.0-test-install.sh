#! /bin/sh
#
# Test script for memtester
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/memtester/memtester.4.3.0.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/memtester.4.3.0/README
/bin/rm -f /var/opt/UNItools/docs/memtester.4.3.0/memtester.txt
/bin/rm -f /var/opt/UNItools/docs/memtester.4.3.0/memtester.pdf
/bin/rm -f /var/opt/UNItools/docs/memtester.4.3.0/README.tests
/bin/rm -f /var/opt/UNItools/docs/memtester.4.3.0/COPYING
/bin/rm -f /var/opt/UNItools/docs/memtester.4.3.0/CHANGELOG
/bin/rm -f /var/opt/UNItools/docs/memtester.4.3.0/memtester.html
/bin/rm -f /var/opt/UNItools/bin/memtester
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/memtester.4.3.0/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/memtester.4.3.0/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/memtester.4.3.0/memtester.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/memtester.4.3.0/memtester.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/memtester.4.3.0/memtester.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/memtester.4.3.0/memtester.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/memtester.4.3.0/README.tests ]; then
	echo "ERROR: file /var/opt/UNItools/docs/memtester.4.3.0/README.tests exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/memtester.4.3.0/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/memtester.4.3.0/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/memtester.4.3.0/CHANGELOG ]; then
	echo "ERROR: file /var/opt/UNItools/docs/memtester.4.3.0/CHANGELOG exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/memtester.4.3.0/memtester.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/memtester.4.3.0/memtester.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/memtester ]; then
	echo "ERROR: file /var/opt/UNItools/bin/memtester exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/memtester
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

