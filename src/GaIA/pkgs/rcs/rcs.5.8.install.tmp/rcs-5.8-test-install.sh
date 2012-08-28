#! /bin/sh
#
# Test script for rcs
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/rcs/rcs.5.8.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/share/info/rcs.info
/bin/rm -f /var/opt/UNItools/share/info/dir
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/ci.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rlog.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsintro.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcs.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcs.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsmerge.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsmerge.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rlog.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsmerge.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcs.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/ci.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/merge.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/README
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/co.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/ident.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/ci.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsclean.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/ident.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsfile.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/NEWS
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsfile.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/merge.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsdiff.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rlog.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsintro.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsintro.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsclean.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsdiff.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/co.html
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/COPYING
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/ident.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsdiff.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsfile.txt
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/merge.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/co.pdf
/bin/rm -f /var/opt/UNItools/docs/rcs.5.8/rcsclean.txt
/bin/rm -f /var/opt/UNItools/bin/co
/bin/rm -f /var/opt/UNItools/bin/rlog
/bin/rm -f /var/opt/UNItools/bin/ident
/bin/rm -f /var/opt/UNItools/bin/rcs
/bin/rm -f /var/opt/UNItools/bin/rcsmerge
/bin/rm -f /var/opt/UNItools/bin/merge
/bin/rm -f /var/opt/UNItools/bin/ci
/bin/rm -f /var/opt/UNItools/bin/rcsdiff
/bin/rm -f /var/opt/UNItools/bin/rcsclean
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/share/info/rcs.info ]; then
	echo "ERROR: file /var/opt/UNItools/share/info/rcs.info exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/info/dir ]; then
	echo "ERROR: file /var/opt/UNItools/share/info/dir exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/ci.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/ci.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rlog.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rlog.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsintro.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsintro.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcs.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcs.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcs.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcs.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsmerge.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsmerge.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsmerge.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsmerge.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rlog.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rlog.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsmerge.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsmerge.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcs.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcs.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/ci.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/ci.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/merge.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/merge.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/co.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/co.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/ident.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/ident.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/ci.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/ci.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsclean.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsclean.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/ident.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/ident.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsfile.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsfile.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsfile.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsfile.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/merge.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/merge.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsdiff.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsdiff.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rlog.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rlog.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsintro.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsintro.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsintro.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsintro.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsclean.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsclean.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsdiff.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsdiff.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/co.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/co.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/ident.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/ident.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsdiff.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsdiff.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsfile.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsfile.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/merge.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/merge.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/co.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/co.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/rcs.5.8/rcsclean.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/rcs.5.8/rcsclean.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/co ]; then
	echo "ERROR: file /var/opt/UNItools/bin/co exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/rlog ]; then
	echo "ERROR: file /var/opt/UNItools/bin/rlog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/ident ]; then
	echo "ERROR: file /var/opt/UNItools/bin/ident exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/rcs ]; then
	echo "ERROR: file /var/opt/UNItools/bin/rcs exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/rcsmerge ]; then
	echo "ERROR: file /var/opt/UNItools/bin/rcsmerge exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/merge ]; then
	echo "ERROR: file /var/opt/UNItools/bin/merge exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/ci ]; then
	echo "ERROR: file /var/opt/UNItools/bin/ci exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/rcsdiff ]; then
	echo "ERROR: file /var/opt/UNItools/bin/rcsdiff exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/rcsclean ]; then
	echo "ERROR: file /var/opt/UNItools/bin/rcsclean exists"
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

