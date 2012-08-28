#!/bin/sh
#
#
builtin_remove() {
# Remove files from archive
cd /
/bin/rm -f ./var/opt/UNItools/docs/SP/di.4.2/LICENSE
/bin/rm -f ./var/opt/UNItools/docs/SP/di.4.2/LICENSE.iffe
/bin/rm -f ./var/opt/UNItools/docs/SP/di.4.2/README
/bin/rm -f ./var/opt/UNItools/docs/SP/di.4.2/index.html
/bin/rm -f ./var/opt/UNItools/docs/SP/di.4.2/.info
/bin/rm -f ./var/opt/UNItools/setup/di.4.2.dependency_check.sh
/bin/rmdir ./var/opt/UNItools/docs/di.4.2
}

builtin_check() {

	echo "check package dependencies ... "
	rpm -q glibc-2.3.2-95.33

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

