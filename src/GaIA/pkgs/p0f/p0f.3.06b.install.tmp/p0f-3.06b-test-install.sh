#! /bin/sh
#
# Test script for p0f
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/p0f/p0f.3.06b.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/p0f.3.06b/README-TOOLS
/bin/rm -f /var/opt/UNItools/docs/p0f.3.06b/README
/bin/rm -f /var/opt/UNItools/docs/p0f.3.06b/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/p0f.3.06b/COPYING
/bin/rm -f /var/opt/UNItools/etc/p0f.fp
/bin/rm -f /var/opt/UNItools/bin/p0f
/bin/rm -f /var/opt/UNItools/bin/p0f-sendsyn
/bin/rm -f /var/opt/UNItools/bin/p0f-sendsyn6
/bin/rm -f /var/opt/UNItools/bin/p0f-client
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/p0f.3.06b/README-TOOLS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/p0f.3.06b/README-TOOLS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/p0f.3.06b/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/p0f.3.06b/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/p0f.3.06b/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/p0f.3.06b/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/p0f.3.06b/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/p0f.3.06b/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/etc/p0f.fp ]; then
	echo "ERROR: file /var/opt/UNItools/etc/p0f.fp exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/p0f ]; then
	echo "ERROR: file /var/opt/UNItools/bin/p0f exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/p0f-sendsyn ]; then
	echo "ERROR: file /var/opt/UNItools/bin/p0f-sendsyn exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/p0f-sendsyn6 ]; then
	echo "ERROR: file /var/opt/UNItools/bin/p0f-sendsyn6 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/p0f-client ]; then
	echo "ERROR: file /var/opt/UNItools/bin/p0f-client exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/p0f-sendsyn
ldd /var/opt/UNItools/bin/p0f-sendsyn6
ldd /var/opt/UNItools/bin/p0f-client
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

