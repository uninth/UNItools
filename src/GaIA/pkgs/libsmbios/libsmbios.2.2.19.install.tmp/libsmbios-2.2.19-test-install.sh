#! /bin/sh
#
# Test script for libsmbios
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/libsmbios/libsmbios.2.2.19.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/lib/libsmbios.a
/bin/rm -f /var/opt/UNItools/lib/libsmbios_c.la
/bin/rm -f /var/opt/UNItools/lib/libsmbios.la
/bin/rm -f /var/opt/UNItools/lib/libsmbios.so.2.1.0
/bin/rm -f /var/opt/UNItools/lib/libsmbios_c.so.2.2.1
/bin/rm -f /var/opt/UNItools/lib/pkgconfig/libsmbios_c.pc
/bin/rm -f /var/opt/UNItools/lib/pkgconfig/libsmbios_c++.pc
/bin/rm -f /var/opt/UNItools/lib/libsmbios_c.a
/bin/rm -f /var/opt/UNItools/bin/smbios-state-byte-ctl
/bin/rm -f /var/opt/UNItools/bin/dellLEDCtl
/bin/rm -f /var/opt/UNItools/bin/dellBiosUpdate-compat
/bin/rm -f /var/opt/UNItools/bin/smbios-get-ut-data
/bin/rm -f /var/opt/UNItools/bin/smbios-sys-info-lite
/bin/rm -f /var/opt/UNItools/bin/smbios-upflag-ctl
/bin/rm -f /var/opt/UNItools/bin/dellMediaDirectCtl
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/LICENSE
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING-OSL
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/README
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/readme.txt
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/NEWS
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/getopts_LICENSE.txt
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/AUTHORS
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING-GPL
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/old_news.txt
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/boost_LICENSE_1_0_txt
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING
/bin/rm -f /var/opt/UNItools/docs/libsmbios.2.2.19/ChangeLog
/bin/rm -f /var/opt/UNItools/share/locale/es/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/en@boldquot/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/en@quot/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/en/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/fr/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/nl/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/de/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/ja/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/ko/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/it/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/zh_TW/LC_MESSAGES/libsmbios.mo
/bin/rm -f /var/opt/UNItools/share/locale/zh_CN/LC_MESSAGES/libsmbios.mo
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/lib/libsmbios.a ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libsmbios.a exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/libsmbios_c.la ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libsmbios_c.la exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/libsmbios.la ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libsmbios.la exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/libsmbios.so.2.1.0 ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libsmbios.so.2.1.0 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/libsmbios_c.so.2.2.1 ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libsmbios_c.so.2.2.1 exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/pkgconfig/libsmbios_c.pc ]; then
	echo "ERROR: file /var/opt/UNItools/lib/pkgconfig/libsmbios_c.pc exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/pkgconfig/libsmbios_c++.pc ]; then
	echo "ERROR: file /var/opt/UNItools/lib/pkgconfig/libsmbios_c++.pc exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/lib/libsmbios_c.a ]; then
	echo "ERROR: file /var/opt/UNItools/lib/libsmbios_c.a exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/smbios-state-byte-ctl ]; then
	echo "ERROR: file /var/opt/UNItools/bin/smbios-state-byte-ctl exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/dellLEDCtl ]; then
	echo "ERROR: file /var/opt/UNItools/bin/dellLEDCtl exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/dellBiosUpdate-compat ]; then
	echo "ERROR: file /var/opt/UNItools/bin/dellBiosUpdate-compat exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/smbios-get-ut-data ]; then
	echo "ERROR: file /var/opt/UNItools/bin/smbios-get-ut-data exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/smbios-sys-info-lite ]; then
	echo "ERROR: file /var/opt/UNItools/bin/smbios-sys-info-lite exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/smbios-upflag-ctl ]; then
	echo "ERROR: file /var/opt/UNItools/bin/smbios-upflag-ctl exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/dellMediaDirectCtl ]; then
	echo "ERROR: file /var/opt/UNItools/bin/dellMediaDirectCtl exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/LICENSE ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/LICENSE exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING-OSL ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING-OSL exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/README ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/README exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/readme.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/readme.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/NEWS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/NEWS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/getopts_LICENSE.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/getopts_LICENSE.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/AUTHORS ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/AUTHORS exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING-GPL ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING-GPL exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/old_news.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/old_news.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/boost_LICENSE_1_0_txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/boost_LICENSE_1_0_txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/COPYING exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/libsmbios.2.2.19/ChangeLog ]; then
	echo "ERROR: file /var/opt/UNItools/docs/libsmbios.2.2.19/ChangeLog exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/es/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/es/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/en@boldquot/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/en@boldquot/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/en@quot/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/en@quot/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/en/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/en/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/fr/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/fr/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/nl/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/nl/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/de/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/de/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/ja/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/ja/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/ko/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/ko/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/it/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/it/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/zh_TW/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/zh_TW/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/share/locale/zh_CN/LC_MESSAGES/libsmbios.mo ]; then
	echo "ERROR: file /var/opt/UNItools/share/locale/zh_CN/LC_MESSAGES/libsmbios.mo exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/smbios-state-byte-ctl
ldd /var/opt/UNItools/bin/dellLEDCtl
ldd /var/opt/UNItools/bin/dellBiosUpdate-compat
ldd /var/opt/UNItools/bin/smbios-get-ut-data
ldd /var/opt/UNItools/bin/smbios-sys-info-lite
ldd /var/opt/UNItools/bin/smbios-upflag-ctl
ldd /var/opt/UNItools/bin/dellMediaDirectCtl
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

