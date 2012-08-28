#! /bin/sh
#
# Test script for ofiller
#
ERROR=0
TMPROOT=/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/ofiller/ofiller.2.0.install.tmp

function rmfiles()
{
	echo "removing files ..."
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/ofiller.pl
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/README_FOR_HTML.TXT
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/ofiller.html
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Users_Manual.pdf
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Martin_Hoz.asc
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/README_FOR_LINUX_AND_SPLAT.TXT
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_list2.csv
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_list1.csv
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_objects_5_0.C
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_csv.csv
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_rules.csv
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_hosts
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_rulebases_5_0.fws
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_pix.txt
/bin/rm -f /var/opt/UNItools/docs/GT/ofiller.2.0/README.TXT
/bin/rm -f /var/opt/UNItools/docs/ofiller.2.0/README_FOR_WINDOWS.TXT
/bin/rm -f /var/opt/UNItools/docs/ofiller.2.0/README_FOR_LINUX_AND_SPLAT.TXT
/bin/rm -f /var/opt/UNItools/docs/ofiller.2.0/README.TXT
/bin/rm -f /var/opt/UNItools/docs/ofiller.2.0/README_FOR_HTML.TXT
/bin/rm -f /var/opt/UNItools/bin/ofiller
/bin/rm -f /var/opt/UNItools/bin/odumper
}

function test_noclobber()
{
	echo "testing that installation will not clobber existing files"
if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/ofiller.pl ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/ofiller.pl exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/README_FOR_HTML.TXT ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/README_FOR_HTML.TXT exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/ofiller.html ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/HTML/ofiller.html exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Users_Manual.pdf ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Users_Manual.pdf exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Martin_Hoz.asc ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Martin_Hoz.asc exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/README_FOR_LINUX_AND_SPLAT.TXT ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/README_FOR_LINUX_AND_SPLAT.TXT exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_list2.csv ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_list2.csv exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_list1.csv ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_list1.csv exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_objects_5_0.C ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_objects_5_0.C exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_csv.csv ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_csv.csv exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_rules.csv ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_rules.csv exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_hosts ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_hosts exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_rulebases_5_0.fws ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_rulebases_5_0.fws exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_pix.txt ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/Samples/sample_pix.txt exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/GT/ofiller.2.0/README.TXT ]; then
	echo "ERROR: file /var/opt/UNItools/docs/GT/ofiller.2.0/README.TXT exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/ofiller.2.0/README_FOR_WINDOWS.TXT ]; then
	echo "ERROR: file /var/opt/UNItools/docs/ofiller.2.0/README_FOR_WINDOWS.TXT exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/ofiller.2.0/README_FOR_LINUX_AND_SPLAT.TXT ]; then
	echo "ERROR: file /var/opt/UNItools/docs/ofiller.2.0/README_FOR_LINUX_AND_SPLAT.TXT exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/ofiller.2.0/README.TXT ]; then
	echo "ERROR: file /var/opt/UNItools/docs/ofiller.2.0/README.TXT exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/docs/ofiller.2.0/README_FOR_HTML.TXT ]; then
	echo "ERROR: file /var/opt/UNItools/docs/ofiller.2.0/README_FOR_HTML.TXT exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/ofiller ]; then
	echo "ERROR: file /var/opt/UNItools/bin/ofiller exists"
	ERROR=1
fi

if [ -f /var/opt/UNItools/bin/odumper ]; then
	echo "ERROR: file /var/opt/UNItools/bin/odumper exists"
	ERROR=1
fi
}

function test_shared_libs()
{
	if [ -s /tmp/test_ldd_files ]; then
		echo "testing that all shared libs are available:"
	(
	ldd /var/opt/UNItools/bin/ofiller
ldd /var/opt/UNItools/bin/odumper
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

