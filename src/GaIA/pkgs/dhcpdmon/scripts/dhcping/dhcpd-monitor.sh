#!/bin/sh
#
# se http://www.mavetju.org/unix/dhcping-man.php
#
# $Header: /lan/ssi/projects/UNItools/src/SPLAT/NGX/pkgs/dhcpdmon/scripts/dhcping/dhcpd-monitor.sh,v 1.1 2009/08/26 14:34:52 root Exp $
#
# Kaldes af fra /etc/init.d/dhcpdmon

TMPF=/tmp/dhcping.out

CONFIG=/home/admin/.dhcping.conf

if [ -f "${CONFIG}" ]; then
	. "${CONFIG}"
else
	 /usr/bin/logger -p mail.crit -t DHCP-MONITOR no configfile, bye
	 exit 1
fi

while :;
do

	/var/opt/UNItools/bin/dhcping -v -s "${PING_IP}" -t "${INTERVAL}" > $TMPF 2>&1
	case $? in
		0)	: # ok
		;;
		*)	# bad - restart server

			(
				echo "dhcpd server restarted, reason below:"
				echo "dhcping -v -s ${PING_IP} -t ${INTERVAL}: bad answer, restarting server"
				cat $TMPF
				/etc/init.d/dhcpd status
				/etc/init.d/dhcpd stop
				echo "sleeping 10 sec .... "
				sleep 10
				/etc/init.d/dhcpd start
				echo server restarted
			) 2>&1 | /usr/bin/logger -p mail.crit -t DHCP-MONITOR 
		;;
	esac

	sleep 60
done

