#!/bin/sh
#
#
builtin_remove() {
# Remove files from archive
cd /
/bin/rm -f ./var/opt/UNItools/bin/dnstop
/bin/rm -f ./var/opt/UNItools/docs/NT/dnstop.20050405/LICENSE
/bin/rm -f ./var/opt/UNItools/docs/NT/dnstop.20050405/dnstop.html
/bin/rm -f ./var/opt/UNItools/docs/NT/dnstop.20050405/dnstop.txt
/bin/rm -f ./var/opt/UNItools/docs/NT/dnstop.20050405/dnstop.pdf
/bin/rm -f ./var/opt/UNItools/docs/NT/dnstop.20050405/index.html
/bin/rm -f ./var/opt/UNItools/docs/NT/dnstop.20050405/.info
/bin/rm -f ./var/opt/UNItools/setup/dnstop.20050405.dependency_check.sh
/bin/rmdir ./var/opt/UNItools/docs/dnstop.20050405
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

