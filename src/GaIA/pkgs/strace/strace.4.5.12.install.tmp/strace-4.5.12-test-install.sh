#! /bin/sh
#
# Test script for strace
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/strace/strace.4.5.12.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/README
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/README-sunos4
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/NEWS
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/README-linux
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/README-CVS
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/README-svr4
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/changelog
/bin/rm -f /var/opt/UNItools/docs/strace.4.5.12/README-freebsd
/bin/rm -f /var/opt/UNItools/bin/strace-graph
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/strace.4.5.12/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/README-sunos4 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/README-sunos4 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/README-linux ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/README-linux exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/README-CVS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/README-CVS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/README-svr4 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/README-svr4 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/changelog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/changelog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strace.4.5.12/README-freebsd ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strace.4.5.12/README-freebsd exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/strace-graph ]; then
	echo "ERROR: file /var/opt/UNItools/bin/strace-graph exists"
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

