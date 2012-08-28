#! /bin/sh
#
# Test script for smtpclient
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/smtpclient/smtpclient.1.0.0.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/bin/smtpclient
/bin/rm -f /var/opt/UNItools/docs/smtpclient.1.0.0/LICENSE
/bin/rm -f /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.html
/bin/rm -f /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.pdf
/bin/rm -f /var/opt/UNItools/docs/smtpclient.1.0.0/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/smtpclient.1.0.0/README
/bin/rm -f /var/opt/UNItools/docs/smtpclient.1.0.0/newvers
/bin/rm -f /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.txt
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/bin/smtpclient ]; then
	echo "ERROR: file /var/opt/UNItools/bin/smtpclient exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/smtpclient.1.0.0/LICENSE ]; then
	echo "ERROR: file /var/opt/UNItools/docs/smtpclient.1.0.0/LICENSE exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/smtpclient.1.0.0/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/smtpclient.1.0.0/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/smtpclient.1.0.0/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/smtpclient.1.0.0/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/smtpclient.1.0.0/newvers ]; then
	echo "ERROR: file /var/opt/UNItools/docs/smtpclient.1.0.0/newvers exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/smtpclient.1.0.0/smtpclient.txt exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/smtpclient
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

