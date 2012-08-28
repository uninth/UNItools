#! /bin/sh
#
# Test script for strings
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/strings/strings.2.14.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/lib/libiberty.a
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9899
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/jal-newabi.s
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/README
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9697
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ld-new
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/NEWS
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/news.h
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/strip-new
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9495
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9193
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/mpw-README
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/newsos3.c
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/as-new
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9295
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9297
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/opcodes_new.d
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/copying-lib.texi
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9197
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/COPYING.LIB
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/COPYING
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/README-vms
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/jal-newabi.d
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/nm-new
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/te-lnews.h
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/mipslnews.sh
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/news.sh
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-0001
/bin/rm -f /var/opt/UNItools/docs/strings.2.14/news-mips.h
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/lib/libiberty.a ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libiberty.a exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9899 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog-9899 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/jal-newabi.s ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/jal-newabi.s exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9697 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog-9697 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ld-new ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ld-new exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/news.h ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/news.h exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/strip-new ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/strip-new exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9495 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog-9495 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9193 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog-9193 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/mpw-README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/mpw-README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/newsos3.c ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/newsos3.c exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/as-new ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/as-new exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9295 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog-9295 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9297 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog-9297 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/opcodes_new.d ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/opcodes_new.d exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/copying-lib.texi ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/copying-lib.texi exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-9197 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog-9197 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/COPYING.LIB ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/COPYING.LIB exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/README-vms ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/README-vms exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/jal-newabi.d ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/jal-newabi.d exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/nm-new ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/nm-new exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/te-lnews.h ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/te-lnews.h exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/mipslnews.sh ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/mipslnews.sh exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/news.sh ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/news.sh exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/ChangeLog-0001 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/ChangeLog-0001 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/strings.2.14/news-mips.h ]; then
	echo "ERROR: file /var/opt/UNItools/docs/strings.2.14/news-mips.h exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/docs/strings.2.14/ld-new
ldd /var/opt/UNItools/docs/strings.2.14/strip-new
ldd /var/opt/UNItools/docs/strings.2.14/as-new
ldd /var/opt/UNItools/docs/strings.2.14/nm-new
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

