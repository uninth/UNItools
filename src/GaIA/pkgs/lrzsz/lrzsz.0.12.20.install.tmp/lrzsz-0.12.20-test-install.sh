#! /bin/sh
#
# Test script for lrzsz
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/lrzsz/lrzsz.0.12.20.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/README.cvs
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.pdf
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/changelog
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.html
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/README.tests
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.pdf
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/newer.exp
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.html
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/NEWS
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/COPYING
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/README
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.txt
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/README.gettext
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.txt
/bin/rm -f /var/opt/UNItools/docs/lrzsz.0.12.20/README.isdn4linux
/bin/rm -f /var/opt/UNItools/bin/lsx
/bin/rm -f /var/opt/UNItools/bin/lrb
/bin/rm -f /var/opt/UNItools/bin/lrx
/bin/rm -f /var/opt/UNItools/bin/lsb
/bin/rm -f /var/opt/UNItools/bin/lrz
/bin/rm -f /var/opt/UNItools/bin/lsz
/bin/rm -f /var/opt/UNItools/share/locale/de/LC_MESSAGES/lrzsz.mo
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/README.cvs ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/README.cvs exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/changelog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/changelog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/README.tests ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/README.tests exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/newer.exp ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/newer.exp exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/lsz.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/README.gettext ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/README.gettext exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/lrz.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lrzsz.0.12.20/README.isdn4linux ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lrzsz.0.12.20/README.isdn4linux exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/lsx ]; then
	echo "ERROR: file /var/opt/UNItools/bin/lsx exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/lrb ]; then
	echo "ERROR: file /var/opt/UNItools/bin/lrb exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/lrx ]; then
	echo "ERROR: file /var/opt/UNItools/bin/lrx exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/lsb ]; then
	echo "ERROR: file /var/opt/UNItools/bin/lsb exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/lrz ]; then
	echo "ERROR: file /var/opt/UNItools/bin/lrz exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/lsz ]; then
	echo "ERROR: file /var/opt/UNItools/bin/lsz exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/de/LC_MESSAGES/lrzsz.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/de/LC_MESSAGES/lrzsz.mo exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/lsx
ldd /var/opt/UNItools/bin/lrb
ldd /var/opt/UNItools/bin/lrx
ldd /var/opt/UNItools/bin/lsb
ldd /var/opt/UNItools/bin/lrz
ldd /var/opt/UNItools/bin/lsz
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

