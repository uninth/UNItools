#! /bin/sh
#
# Test script for screen
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/screen/screen.4.0.3.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/cd
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/c3
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/d6
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/c2
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/19
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/a1
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/04
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/c4
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/01
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/02
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/bf
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/c7
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/cc
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/c6
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/c8
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/03
/bin/rm -f /var/opt/UNItools/share/screen/utf8encodings/18
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/README.DOTSCREEN
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/newsyntax
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/README
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/screen.html
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.7
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/NEWS
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.5
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.9
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.6
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/screen.txt
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/COPYING
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/newsyntax38
/bin/rm -f /var/opt/UNItools/docs/screen.4.0.3/screen.pdf
/bin/rm -f /var/opt/UNItools/info/screen.info-4
/bin/rm -f /var/opt/UNItools/info/screen.info-3
/bin/rm -f /var/opt/UNItools/info/screen.info-2
/bin/rm -f /var/opt/UNItools/info/dir
/bin/rm -f /var/opt/UNItools/info/screen.info-1
/bin/rm -f /var/opt/UNItools/info/screen.info-5
/bin/rm -f /var/opt/UNItools/info/screen.info
/bin/rm -f /var/opt/UNItools/etc/etcscreenrc
/bin/rm -f /var/opt/UNItools/bin/screen-4.0.3
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/share/screen/utf8encodings/cd ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/cd exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/c3 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/c3 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/d6 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/d6 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/c2 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/c2 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/19 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/19 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/a1 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/a1 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/04 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/04 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/c4 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/c4 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/01 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/01 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/02 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/02 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/bf ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/bf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/c7 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/c7 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/cc ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/cc exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/c6 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/c6 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/c8 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/c8 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/03 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/03 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/screen/utf8encodings/18 ]; then
	echo "ERROR: file /var/opt/UNItools/share/screen/utf8encodings/18 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/README.DOTSCREEN ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/README.DOTSCREEN exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/newsyntax ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/newsyntax exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/screen.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/screen.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.7 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.7 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.5 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.5 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.9 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.9 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.6 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/NEWS.3.6 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/screen.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/screen.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/newsyntax38 ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/newsyntax38 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/screen.4.0.3/screen.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/screen.4.0.3/screen.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/info/screen.info-4 ]; then
	echo "ERROR: file /var/opt/UNItools/info/screen.info-4 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/info/screen.info-3 ]; then
	echo "ERROR: file /var/opt/UNItools/info/screen.info-3 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/info/screen.info-2 ]; then
	echo "ERROR: file /var/opt/UNItools/info/screen.info-2 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/info/dir ]; then
	echo "ERROR: file /var/opt/UNItools/info/dir exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/info/screen.info-1 ]; then
	echo "ERROR: file /var/opt/UNItools/info/screen.info-1 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/info/screen.info-5 ]; then
	echo "ERROR: file /var/opt/UNItools/info/screen.info-5 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/info/screen.info ]; then
	echo "ERROR: file /var/opt/UNItools/info/screen.info exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/etc/etcscreenrc ]; then
	echo "ERROR: file /var/opt/UNItools/etc/etcscreenrc exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/screen-4.0.3 ]; then
	echo "ERROR: file /var/opt/UNItools/bin/screen-4.0.3 exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/screen-4.0.3
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

