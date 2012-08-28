#!/bin/sh
#
# $Header: /lan/ssi/projects/UNItools/src/SPLAT/NGX/pkgs/unbound_dns/setup.sh,v 1.4 2013/05/29 10:25:15 root Exp $
#

#
# Vars
#
UNBOUNDUSER=unbound
UNBOUNDGROUP="${UNBOUNDUSER}"
ROOTDIR="/home/${UNBOUNDUSER}"

PATH=$PATH:$ROOTDIR/bin

case $1 in
	install)

		FOUND=`clish -c "show user $UNBOUNDUSER" 2>&1	|
			awk '$3 == "'${ROOTDIR}'" {
				print "TRUE"
			}'`

		case $FOUND in
			TRUE)	echo "user '$UNBOUNDUSER' exists run $0 uninstall, bye"
				exit 1
			;;
			"")	:
			;;
			*)
			;;
		esac

		cat <<- EOF | clish 
		lock database override
		add user $UNBOUNDUSER uid 1004 homedir $ROOTDIR
		set user $UNBOUNDUSER shell /sbin/nologin
		save config
		quit
EOF
		
		#
		# Jeg er ikke sikker på at det er den rigtige måde at gøre det følgende på
		#

		# Add start/stop script
		INIT=$ROOTDIR/etc/unbound.init
		cp $INIT /etc/init.d/unbound
		chkconfig --add unbound
		chmod 555 /etc/init.d/unbound

		# Preserve old file
		test -f /etc/sysconfig/syslog.org || {
			/bin/cp /etc/sysconfig/syslog /etc/sysconfig/syslog.org
		}
		
		#
		# Add -a $ROOTDIR/dev/log to /etc/sysconfig/syslog
		#
		. /etc/sysconfig/syslog.org

		SYSLOGD_OPTIONS="${SYSLOGD_OPTIONS} -a $ROOTDIR/dev/log"

		sed "s%^SYSLOGD_OPTIONS.*%SYSLOGD_OPTIONS=\"${SYSLOGD_OPTIONS}\"%" /etc/sysconfig/syslog.org > /tmp/syslog

		/bin/mv /tmp/syslog /etc/sysconfig/syslog
		/etc/init.d/syslog restart

		# A copy is already here so it doesn't matter if wget fails
		cd $ROOTDIR/etc/unbound
		wget ftp://ftp.internic.net/domain/named.cache

		cd  $ROOTDIR/bin
		$ROOTDIR/bin/unbound-control-setup

		/etc/init.d/unbound start
	;;
	uninstall)

		chkconfig --del unbound
		/bin/rm -f /etc/init.d/unbound

		test -f /etc/sysconfig/syslog.org || {
			/bin/cp /etc/sysconfig/syslog /etc/sysconfig/syslog.org
		}

		#
		# Remove -a $ROOTDIR/dev/log from syslog options by reversing to vanilla
		#

		SYSLOGD_OPTIONS="-m 0 -z 515"

		sed "s%^SYSLOGD_OPTIONS.*%SYSLOGD_OPTIONS=\"${SYSLOGD_OPTIONS}\"%" /etc/sysconfig/syslog.org > /tmp/syslog

		/bin/mv /tmp/syslog /etc/sysconfig/syslog
		/etc/init.d/syslog restart

		# Remove user -- which will remove HOME as well

		cd /

		cat <<- EOF | clish 
		lock database override
		delete user $UNBOUNDUSER
		save config
		quit
EOF

	;;
esac
