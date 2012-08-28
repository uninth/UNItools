#! /bin/sh
#
# Test script for minicom
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/minicom/minicom.2.1.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/share/locale/pt_BR/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/share/locale/ru/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/share/locale/ja/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/share/locale/hu/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/share/locale/fr/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/share/locale/es/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/share/locale/cs/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/share/locale/pl/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/share/locale/fi/LC_MESSAGES/minicom.mo
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/runscript.pdf
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/ChangeLog.old
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/minicom.pdf
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/runscript.txt
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/runscript.html
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/README-FIRST
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/xminicom.html
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/minicom.txt
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/README
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/xminicom.txt
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.txt
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/minicom.html
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/ChangeLog
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/NEWS
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/modemu.README
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.html
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/README.lrzsz
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/xminicom.pdf
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/COPYING
/bin/rm -f /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.pdf
/bin/rm -f /var/opt/UNItools/bin/minicom
/bin/rm -f /var/opt/UNItools/bin/xminicom
/bin/rm -f /var/opt/UNItools/bin/ascii-xfr
/bin/rm -f /var/opt/UNItools/bin/runscript
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/share/locale/pt_BR/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/pt_BR/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/ru/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/ru/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/ja/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/ja/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/hu/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/hu/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/fr/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/fr/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/es/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/es/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/cs/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/cs/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/pl/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/pl/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/fi/LC_MESSAGES/minicom.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/fi/LC_MESSAGES/minicom.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/runscript.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/runscript.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/ChangeLog.old ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/ChangeLog.old exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/minicom.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/minicom.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/runscript.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/runscript.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/runscript.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/runscript.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/README-FIRST ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/README-FIRST exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/xminicom.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/xminicom.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/minicom.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/minicom.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/xminicom.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/xminicom.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/minicom.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/minicom.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/modemu.README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/modemu.README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/README.lrzsz ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/README.lrzsz exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/xminicom.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/xminicom.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/minicom.2.1/ascii-xfr.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/minicom ]; then
	echo "ERROR: file /var/opt/UNItools/bin/minicom exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/xminicom ]; then
	echo "ERROR: file /var/opt/UNItools/bin/xminicom exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/ascii-xfr ]; then
	echo "ERROR: file /var/opt/UNItools/bin/ascii-xfr exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/runscript ]; then
	echo "ERROR: file /var/opt/UNItools/bin/runscript exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/minicom
ldd /var/opt/UNItools/bin/ascii-xfr
ldd /var/opt/UNItools/bin/runscript
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

