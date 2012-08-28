#! /bin/sh
#
# Test script for hping
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/hping/hping.2.0.0-rc3.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.txt
/bin/rm -f /var/opt/UNItools/docs/hping.2.0.0-rc3/SPOOFED_SCAN.txt
/bin/rm -f /var/opt/UNItools/docs/hping.2.0.0-rc3/HPING2-IS-OPEN
/bin/rm -f /var/opt/UNItools/docs/hping.2.0.0-rc3/HPING2-HOWTO.txt
/bin/rm -f /var/opt/UNItools/docs/hping.2.0.0-rc3/MORE-FUN-WITH-IPID
/bin/rm -f /var/opt/UNItools/docs/hping.2.0.0-rc3/APD.txt
/bin/rm -f /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.html
/bin/rm -f /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.pdf
/bin/rm -f /var/opt/UNItools/bin/hping2
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/hping.2.0.0-rc3/SPOOFED_SCAN.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/hping.2.0.0-rc3/SPOOFED_SCAN.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/hping.2.0.0-rc3/HPING2-IS-OPEN ]; then
	echo "ERROR: file /var/opt/UNItools/docs/hping.2.0.0-rc3/HPING2-IS-OPEN exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/hping.2.0.0-rc3/HPING2-HOWTO.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/hping.2.0.0-rc3/HPING2-HOWTO.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/hping.2.0.0-rc3/MORE-FUN-WITH-IPID ]; then
	echo "ERROR: file /var/opt/UNItools/docs/hping.2.0.0-rc3/MORE-FUN-WITH-IPID exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/hping.2.0.0-rc3/APD.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/hping.2.0.0-rc3/APD.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/hping.2.0.0-rc3/hping2.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/hping2 ]; then
	echo "ERROR: file /var/opt/UNItools/bin/hping2 exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/hping2
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

