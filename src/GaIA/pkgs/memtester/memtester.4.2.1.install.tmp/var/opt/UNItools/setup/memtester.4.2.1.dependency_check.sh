#!/bin/sh
#
#
builtin_remove() {
# Remove files from archive
cd /
/bin/rm -f ./var/opt/UNItools/bin/memtester
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/CHANGELOG
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/COPYING
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/README
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/README.tests
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/memtester.html
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/memtester.txt
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/memtester.pdf
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/index.html
/bin/rm -f ./var/opt/UNItools/docs/SPM/memtester.4.2.1/.info
/bin/rm -f ./var/opt/UNItools/setup/memtester.4.2.1.dependency_check.sh
/bin/rmdir ./var/opt/UNItools/docs/memtester.4.2.1
}

builtin_check() {

	echo "check package dependencies ... "
	rpm -q glibc-2.3.2-95.50

	case $? in
		0)	echo "seems ok, try it"
		;;
		*)	echo "not worth trying, you are missing something"
			echo "try make it static"
		;;
	esac

}

case $1 in
	check)	builtin_check
	;;
	remove)	builtin_remove
	;;
	*)	echo "Usage: $0 check | remove"
	;;
esac

exit 0

