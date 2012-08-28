#! /bin/sh
#
# Test script for lshw
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/lshw/lshw.B.02.16.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/COPYING
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/lshw.txt
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/lshw.xsd
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/README
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/IODC.txt
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/lshw.pdf
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/Changelog
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/proc_usb_info.txt
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/lshw.html
/bin/rm -f /var/opt/UNItools/docs/lshw.B.02.16/TODO
/bin/rm -f /var/opt/UNItools/share/lshw/usb.ids
/bin/rm -f /var/opt/UNItools/share/lshw/pci.ids
/bin/rm -f /var/opt/UNItools/share/lshw/oui.txt
/bin/rm -f /var/opt/UNItools/share/lshw/manuf.txt
/bin/rm -f /var/opt/UNItools/share/locale/fr/LC_MESSAGES/lshw.mo
/bin/rm -f /var/opt/UNItools/bin/lshw
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/lshw.B.02.16/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/lshw.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/lshw.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/lshw.xsd ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/lshw.xsd exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/IODC.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/IODC.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/lshw.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/lshw.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/Changelog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/Changelog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/proc_usb_info.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/proc_usb_info.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/lshw.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/lshw.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/lshw.B.02.16/TODO ]; then
	echo "ERROR: file /var/opt/UNItools/docs/lshw.B.02.16/TODO exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/lshw/usb.ids ]; then
	echo "ERROR: file /var/opt/UNItools/share/lshw/usb.ids exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/lshw/pci.ids ]; then
	echo "ERROR: file /var/opt/UNItools/share/lshw/pci.ids exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/lshw/oui.txt ]; then
	echo "ERROR: file /var/opt/UNItools/share/lshw/oui.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/lshw/manuf.txt ]; then
	echo "ERROR: file /var/opt/UNItools/share/lshw/manuf.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/fr/LC_MESSAGES/lshw.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/fr/LC_MESSAGES/lshw.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/lshw ]; then
	echo "ERROR: file /var/opt/UNItools/bin/lshw exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/lshw
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

