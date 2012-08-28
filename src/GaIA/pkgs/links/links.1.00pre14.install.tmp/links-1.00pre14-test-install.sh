#! /bin/sh
#
# Test script for links
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/links/links.1.00pre14.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/links.1.00pre14/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/links.1.00pre14/links.html
/bin/rm -f /var/opt/UNItools/docs/links.1.00pre14/links.txt
/bin/rm -f /var/opt/UNItools/docs/links.1.00pre14/README
/bin/rm -f /var/opt/UNItools/docs/links.1.00pre14/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/links.1.00pre14/NEWS
/bin/rm -f /var/opt/UNItools/docs/links.1.00pre14/links.pdf
/bin/rm -f /var/opt/UNItools/docs/links.1.00pre14/COPYING
/bin/rm -f /var/opt/UNItools/bin/links
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/links.1.00pre14/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/links.1.00pre14/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/links.1.00pre14/links.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/links.1.00pre14/links.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/links.1.00pre14/links.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/links.1.00pre14/links.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/links.1.00pre14/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/links.1.00pre14/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/links.1.00pre14/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/links.1.00pre14/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/links.1.00pre14/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/links.1.00pre14/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/links.1.00pre14/links.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/links.1.00pre14/links.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/links.1.00pre14/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/links.1.00pre14/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/links ]; then
	echo "ERROR: file /var/opt/UNItools/bin/links exists"
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

