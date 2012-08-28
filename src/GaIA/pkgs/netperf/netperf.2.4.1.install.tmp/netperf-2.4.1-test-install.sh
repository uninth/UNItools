#! /bin/sh
#
# Test script for netperf
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/netperf/netperf.2.4.1.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/info/netperf.info
/bin/rm -f /var/opt/UNItools/bin/netserver
/bin/rm -f /var/opt/UNItools/bin/netperf
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/netperf.txt
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/README.hpux
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/README.solaris
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/netserver.pdf
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/NEWS
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/README.ovms
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/README.aix
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/README.windows~
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/netperf.pdf
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/README
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/netserver.txt
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/README.windows
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/COPYING
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/netperf_2.1_manual.pdf
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/netserver.html
/bin/rm -f /var/opt/UNItools/docs/netperf.2.4.1/netperf.html
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/info/netperf.info ]; then
	echo "ERROR: file /var/opt/UNItools/info/netperf.info exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/netserver ]; then
	echo "ERROR: file /var/opt/UNItools/bin/netserver exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/netperf ]; then
	echo "ERROR: file /var/opt/UNItools/bin/netperf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/netperf.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/netperf.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/README.hpux ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/README.hpux exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/README.solaris ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/README.solaris exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/netserver.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/netserver.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/README.ovms ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/README.ovms exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/README.aix ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/README.aix exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/README.windows~ ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/README.windows~ exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/netperf.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/netperf.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/netserver.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/netserver.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/README.windows ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/README.windows exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/netperf_2.1_manual.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/netperf_2.1_manual.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/netserver.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/netserver.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/netperf.2.4.1/netperf.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/netperf.2.4.1/netperf.html exists"
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
	*)			echo "usage: /lan/ssi/shared/software/internal/pkg_tools/bin/pkg_conbat cleanup | test"
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
echo "Clean up by executing /lan/ssi/shared/software/internal/pkg_tools/bin/pkg_conbat cleanup"

