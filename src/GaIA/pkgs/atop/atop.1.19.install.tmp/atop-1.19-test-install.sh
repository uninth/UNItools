#! /bin/sh
#
# Test script for atop
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/atop/atop.1.19.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/atop.1.19/atop.pdf
/bin/rm -f /var/opt/UNItools/docs/atop.1.19/atop.txt
/bin/rm -f /var/opt/UNItools/docs/atop.1.19/README
/bin/rm -f /var/opt/UNItools/docs/atop.1.19/atop.html
/bin/rm -f /var/opt/UNItools/docs/atop.1.19/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/atop.1.19/COPYING
/bin/rm -f /var/opt/UNItools/docs/atop.1.19/AUTHOR
/bin/rm -f /var/opt/UNItools/etc/atop/atop.24hours
/bin/rm -f /var/opt/UNItools/etc/atop/atop.daily
/bin/rm -f /var/opt/UNItools/etc/rc.d/init.d/atop
/bin/rm -f /var/opt/UNItools/bin/atop
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/atop.1.19/atop.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/atop.1.19/atop.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/atop.1.19/atop.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/atop.1.19/atop.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/atop.1.19/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/atop.1.19/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/atop.1.19/atop.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/atop.1.19/atop.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/atop.1.19/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/atop.1.19/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/atop.1.19/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/atop.1.19/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/atop.1.19/AUTHOR ]; then
	echo "ERROR: file /var/opt/UNItools/docs/atop.1.19/AUTHOR exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/etc/atop/atop.24hours ]; then
	echo "ERROR: file /var/opt/UNItools/etc/atop/atop.24hours exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/etc/atop/atop.daily ]; then
	echo "ERROR: file /var/opt/UNItools/etc/atop/atop.daily exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/etc/rc.d/init.d/atop ]; then
	echo "ERROR: file /var/opt/UNItools/etc/rc.d/init.d/atop exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/atop ]; then
	echo "ERROR: file /var/opt/UNItools/bin/atop exists"
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

