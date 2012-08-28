#!/bin/sh
#
#
builtin_remove() {
# Remove files from archive
cd /
/bin/rm -f ./var/opt/UNItools/docs/perl.5.8.7.813/docs/.info
/bin/rm -f ./var/opt/UNItools/docs/perl.5.8.7.813/docs/index.html
/bin/rm -f ./var/opt/UNItools/docs/perl.5.8.7.813/index.html
/bin/rm -f ./var/opt/UNItools/docs/perl.5.8.7.813/.info
/bin/rm -f ./var/opt/UNItools/setup/perl.5.8.7.813.dependency_check.sh
/bin/rmdir ./var/opt/UNItools/docs/perl.5.8.7.813
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

