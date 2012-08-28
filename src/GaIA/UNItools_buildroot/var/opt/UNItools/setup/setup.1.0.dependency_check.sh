#!/bin/sh
#
#
builtin_remove() {
# Remove files from archive
cd /
/bin/rm -f ./var/opt/UNItools/setup/fw1mungle
/bin/rm -f ./var/opt/UNItools/setup/setup.1.0.dependency_check.sh
/bin/rm -f ./setup-1.0-test-install.sh
/bin/rmdir ./var/opt/UNItools/docs/setup.1.0
}

builtin_check() {

	echo "check package dependencies ... "
	rpm -q 

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

