#! /bin/sh
#
# Test script for lighthttpd
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/lighthttpd/lighthttpd.1.4.39.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/lighthttpd.1.4.39/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/lighthttpd.1.4.39/README
/bin/rm -f /var/opt/UNItools/docs/lighthttpd.1.4.39/NEWS
/bin/rm -f /var/opt/UNItools/docs/lighthttpd.1.4.39/newstyle.css
/bin/rm -f /var/opt/UNItools/docs/lighthttpd.1.4.39/COPYING
/bin/rm -f /var/opt/UNItools/docs/lighthttpd.1.4.39/README.FreeBSD
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/lighthttpd.1.4.39/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lighthttpd.1.4.39/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lighthttpd.1.4.39/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lighthttpd.1.4.39/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lighthttpd.1.4.39/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lighthttpd.1.4.39/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lighthttpd.1.4.39/newstyle.css ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lighthttpd.1.4.39/newstyle.css exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lighthttpd.1.4.39/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lighthttpd.1.4.39/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lighthttpd.1.4.39/README.FreeBSD ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lighthttpd.1.4.39/README.FreeBSD exists"
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

