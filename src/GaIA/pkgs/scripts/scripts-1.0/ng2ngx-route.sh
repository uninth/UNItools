#!/bin/sh
#
# $Header: /lan/ssi/projects/UNItools/src/SPLAT/NGX/pkgs/scripts/scripts-1.0/RCS/ng2ngx-route.sh,v 1.1 2006/04/27 10:30:55 admin Exp $
#
#--------------------------------------------------------------------------------------#
#
# convert rh7.3 netstatoutput to NGX format
# Do not print kernel routening (interface) and default gateway
#
# netstat -rn --protocol=inet |
# Kernel IP routing table
# Destination     Gateway         Genmask         Flags   MSS Window  irtt Iface
# 193.89.55.0     0.0.0.0         255.255.255.240 U        40 0          0 eth0
# 193.89.48.192   10.10.0.1       255.255.255.224 UG       40 0          0 eth2
# 193.181.35.0    10.255.3.4      255.255.255.192 UG       40 0          0 eth1.4
# 10.242.9.0      10.242.0.2      255.255.255.0   UG       40 0          0 eth1.3
# 192.168.100.0   0.0.0.0         255.255.255.0   U        40 0          0 eth4
# 10.255.3.0      0.0.0.0         255.255.255.0   U        40 0          0 eth1.4
# 10.242.8.0      10.242.0.2      255.255.255.0   UG       40 0          0 eth1.3
# ...
# ...
# 0.0.0.0         193.89.55.1     0.0.0.0         UG       40 0          0 eth0
#
#--------------------------------------------------------------------------------------#

#
# Vars
#
RH_NETSTAT_CMD="netstat -rn --protocol=inet"

#
# Functions
#
usage() {
# purpose     : Script usage
# arguments   : none
# return value: none
# see also    :
echo $*
cat << EOF

	convert rh7.3 netstat output to NGX format on STDOUT
	Do not print kernel routening (interface) and default gateway

	Usage: `basename $0` [-f file]

	Arguments:
	-f file: Read netstat output from file. Output should be
	         made with the command

		 ${RH_NETSTAT_CMD}

EOF
	exit 2
}

clean_f () {
# purpose     : Clean-up on trapping (signal)
# arguments   : None
# return value: None
# see also    :
	$echo trapped, bye
	exit 
}

#
# clean up on trap(s)
#
trap clean_f 1 2 3 13 15

################################################################################
# Main
################################################################################

echo=/bin/echo
case ${N}$C in
	"") if $echo "\c" | grep c >/dev/null 2>&1; then
		N='-n'
	else
		C='\c'
	fi ;;
esac

#
# Process arguments
#
while getopts g:h:n opt
do
case $opt in
	f)	NETSTAT_FILE=$OPTARG
		USE_CMD=FALSE
		test -f ${NETSTAT_FILE} || {
			usage file not found
		}
	;;
	*)	usage
		exit
	;;
esac
done
shift `expr $OPTIND - 1`

(
	if [ "${USE_CMD}" = "FALSE" ]; then
		cat ${NETSTAT_FILE}
	else
		${RH_NETSTAT_CMD}
	fi
) | sed '
	/^$/d;
	/^Kernel/d;
	/^Destination/d;
	/^#/d;

' | while read DEST GW GENMASK FLAGS MSS WINDOW IRTT IFACE
do
	if [ "${GW}" = "0.0.0.0" -o "${DEST}" = "0.0.0.0" ]; then

		# implicit route due to enabled interface or default gateway
		:
	else
		eval `ipcalc -p $DEST $GENMASK`
		grep -q "$DEST/$PREFIX" /etc/sysconfig/netconf.C
		case $? in
			0)	# found avoid printing
			;;
			1)	# not found

				cat << EOF
		: (route
			:dest ("$DEST/$PREFIX")
			:dev ($IFACE)
			:via ($GW)
			:metric (0)
		)
EOF
			;;
		esac

	fi
done

exit 0

#
# Documentation and  standard disclaimar
#
# Copyright (C) 2001 Niels Thomas Haug�rd
# UNI-C
# http://www.uni-c.dk/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the 
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#
#++
# NAME
#	ng2ngx-route.sh 1
# SUMMARY
#	convert NG IPv4 route info to NGX format
# PACKAGE
#	UNItools
# SYNOPSIS
#	ng2ngx-route.sh [-f file]
# DESCRIPTION
#	\fCng2ngx-route.sh(1)\fR is an ad-hoc script to convert the output
#	of \fCnetstat(1)\fR on NG (aka Red Hat 7.3) IP version 4 route statements
#	to NGX (Red Had Enterprise 3.0).
#	
#	The script is used during upgrade of NG to NGX.
# OPTIONS
# .TP
#	\fC-f\fR\ \fIfile\fR
#	Read route information from \fIfile\fR.
# COMMANDS
#	\fCsh(1)\fR, \fCsed(1)\fR \fCnetstat(1)\fR and \fCawk(1)\fR.
# SEE\ ALSO
#	Documentation for UNItools
# DIAGNOSTICS
#	The scrip prints to STDOUT.
# BUGS
#	Please correct - this is an ad-hoc script.
# VERSION
#	$Date: 2006/04/27 10:30:55 $
# .br
#	$Revision: 1.1 $
# .br
#	$Source: /lan/ssi/projects/UNItools/src/SPLAT/NGX/pkgs/scripts/scripts-1.0/RCS/ng2ngx-route.sh,v $
# .br
#	$State: Exp $
# HISTORY
#	See \fCrlog\fR $Id$
# AUTHOR(S)
#	Niels Thomas Haug�rd
# .br
#	E-mail: thomas@haugaard.net
# .br
#	UNI\(buC
# .br
#	DTU, Building 304
# .br
#	DK-2800 Kgs. Lyngby
#--
