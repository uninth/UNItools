#! /bin/sh
#
# Test script for conf_template
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/conf_template/conf_template.1.0.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/conf/ntp.conf
/bin/rm -f /var/opt/UNItools/conf/smtpclient.SH
/bin/rm -f /var/opt/UNItools/conf/.bash_profile
/bin/rm -f /var/opt/UNItools/conf/UNIprofile
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/conf/ntp.conf ]; then
	echo "ERROR: file /var/opt/UNItools/conf/ntp.conf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/conf/smtpclient.SH ]; then
	echo "ERROR: file /var/opt/UNItools/conf/smtpclient.SH exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/conf/.bash_profile ]; then
	echo "ERROR: file /var/opt/UNItools/conf/.bash_profile exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/conf/UNIprofile ]; then
	echo "ERROR: file /var/opt/UNItools/conf/UNIprofile exists"
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

