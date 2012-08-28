#! /bin/sh
#
# Test script for fwbu
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/fwbu/fwbu.1.0.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/plugin_pack.conf
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/VERSION
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/pre_upgrade_verifier
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/upgrade_import
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/plugin_upgrade_matcher
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/migrate
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/migrate.conf
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/upgrade_export
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/del_revision_files
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/filter_private_data
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/gtar
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/gzip
/bin/rm -f /var/opt/UNItools/fwbu/upgrade_tools/ppidb.conf
/bin/rm -f /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg
/bin/rm -f /var/opt/UNItools/fwbu/etc/extra_files_for_backup.txt
/bin/rm -f /var/opt/UNItools/fwbu/bin/UNIcpfwbu.sh
/bin/rm -f /var/opt/UNItools/fwbu/bin/setup.sh
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/fwbu/upgrade_tools/plugin_pack.conf ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/plugin_pack.conf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/VERSION ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/VERSION exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/pre_upgrade_verifier ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/pre_upgrade_verifier exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/upgrade_import ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/upgrade_import exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/plugin_upgrade_matcher ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/plugin_upgrade_matcher exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/migrate ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/migrate exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/migrate.conf ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/migrate.conf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/upgrade_export ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/upgrade_export exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/del_revision_files ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/del_revision_files exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/filter_private_data ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/filter_private_data exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/gtar ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/gtar exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/gzip ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/gzip exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/upgrade_tools/ppidb.conf ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/upgrade_tools/ppidb.conf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/etc/extra_files_for_backup.txt ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/etc/extra_files_for_backup.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/bin/UNIcpfwbu.sh ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/bin/UNIcpfwbu.sh exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/fwbu/bin/setup.sh ]; then
	echo "ERROR: file /var/opt/UNItools/fwbu/bin/setup.sh exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/fwbu/upgrade_tools/pre_upgrade_verifier
ldd /var/opt/UNItools/fwbu/upgrade_tools/upgrade_import
ldd /var/opt/UNItools/fwbu/upgrade_tools/plugin_upgrade_matcher
ldd /var/opt/UNItools/fwbu/upgrade_tools/migrate
ldd /var/opt/UNItools/fwbu/upgrade_tools/upgrade_export
ldd /var/opt/UNItools/fwbu/upgrade_tools/del_revision_files
ldd /var/opt/UNItools/fwbu/upgrade_tools/filter_private_data
ldd /var/opt/UNItools/fwbu/upgrade_tools/gtar
ldd /var/opt/UNItools/fwbu/upgrade_tools/gzip
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

