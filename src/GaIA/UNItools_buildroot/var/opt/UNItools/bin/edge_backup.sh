#! /var/opt/UNItools/bin/bash
#
# Ad-hoc edge backup 
#
# $Header: /lan/ssi/projects/UNItools/src/SPLAT/NGX/pkgs/edge_backup/edge_backup-1.0/edge_backup.sh,v 1.2 2011/09/07 11:27:54 root Exp $
#
# The edge box'es are located behind NAT devices, but the inside address is accessible
# through the VPN tunnel, as it is part of the encryption domain.
#
#
# Functions
#
logit() {
# purpose     : Timestamp output
# arguments   : Line og stream
# return value: None
# see also    :
        LOGIT_NOW="`/bin/date '+%H:%M:%S (%d/%m)'`"
        STRING="$*"

        if [ -n "${STRING}" ]; then
		logger -p mail.info -t edge_backup "${STRING}"

                if [ "${VERBOSE}" = "TRUE" ]; then
                        $echo "${LOGIT_NOW} ${STRING}"
                fi
        else
                while read LINE
                do
                        if [ -n "${LINE}" ]; then
                                logger -p mail.info -t edge_backup "${LINE}"
                                if [ "${VERBOSE}" = "TRUE" ]; then
                                        $echo "${LOGIT_NOW} ${LINE}"
                                fi
                        fi
                done
        fi
}

################################################################################
# Main
################################################################################

TMPFILE=$HOME/tmp/.$$.SH
LOCKFILE=$HOME/tmp/edge_backup_lock
#
# tmpdir
#
test -d `dirname $TMPFILE` || {
	mkdir `dirname $TMPFILE`
}

# The list of edge which will be backed up by the script is maintained here:
MY_CONFIG=/var/opt/UNItools/etc/edge_backup.cfg
MY_CONFIG_TMPL=/var/opt/UNItools/etc/edge_backup.cfg.template

echo=/bin/echo
case ${N}$C in
        "") if $echo "\c" | grep c >/dev/null 2>&1; then
                N='-n'
        else
                C='\c'
        fi ;;
esac

case $1 in
	"-v")	VERBOSE=TRUE
	;;
	"")		: # normal operation
	;;
	"install")
		#
		# Add crontab
		#
		echo adding crontab ...
		crontab -u admin -l > /tmp/crontab.admin.org
		(
		crontab -u admin -l 2>/dev/null | sed '/edge_backup/d'
		echo '00 7-23 * * * /var/opt/UNItools/bin/edge_backup.sh >/dev/null 2>&1'
		) > ${TMPFILE}
		crontab -u admin ${TMPFILE}
		test -f ${MY_CONFIG} || {
			cp ${MY_CONFIG_TMPL} ${MY_CONFIG}
			echo "made ${MY_CONFIG}"
		}
		echo "Please edit ${MY_CONFIG}"
		exit 0
	;;
	"uninstall")
		echo uinstall
		echo removing crontab entry ...
		crontab -u admin -l 2>/dev/null | sed '/edge_backup/d' > ${TMPFILE}
		crontab -u admin ${TMPFILE}
		echo "Please remove ${MY_CONFIG}"
		exit 0
	;;
	*)	echo "usage: $0 [-v]|install|uninstall"; exit 0
esac

case $# in
	0|1)	:
	;;
	*)	echo "usage: $0 [-v]|install|uninstall"; exit 0
	;;
esac

test -f $MY_CONFIG || {
	echo "error: $MY_CONFIG not found, bye"
	exit 1
}

. $MY_CONFIG


#
# No further configuration below this point
#

let ERRORS=0;

# Setup environment for admin
case `uname` in
	IPSO)		. $HOME/.profile	> /dev/null 2>&1
	;;
	Linux|Solaris)	. $HOME/.bash_profile	> /dev/null 2>&1
			. $HOME/.bashrc		> /dev/null 2>&1
	;;
	*)		. $HOME/.profile	> /dev/null 2>&1
	;;
esac

#
# Setup private environment
#
.  /var/opt/UNItools/conf/smtpclient.SH
.  /var/opt/UNItools/conf/.bash_profile

#
# The following applications are required but may not have been installed on 'older'
# versions of UNItools
#
wget=/var/opt/UNItools/bin/wget
rcs=/var/opt/UNItools/bin/rcs
ci=/var/opt/UNItools/bin/ci
co=/var/opt/UNItools/bin/co
#
# Prevent concurent runs
#
test -f ${LOCKFILE} && {

	logit "${LOCKFILE} found"
	XPID=`cat ${LOCKFILE}`
	FIND_PID=`ps --pid ${XPID} -opid --no-headers`

	if [ "${FIND_PID}" = "${XPID}" ]; then
		logit "abort: running on pid ${FIND_PID}, bye"
		exit 1
	else
		logit "pid ${XPID} not found removing pid file"
	fi
}

echo $$ > ${LOCKFILE}

# Catch the situation where edge'es has been added to the object database but not to the script
# Assume all known edge'es has been added to the group G_Edge, then export the object database
# and compare the group to the list of inside addresses.
# 
# This file is slso used by 'td' - same format/command
# ODUMPER_EXPORT=/tmp/odumper_export.csv
# 
#
# Only (re)-export the database if needed
#
# if [ "$ODUMPER_EXPORT" -ot "$FWDIR/conf/objects_5_0.C" ]; then
# 	/bin/rm -f $ODUMPER_EXPORT
# 	odumper -f $FWDIR/conf/objects_5_0.C -o $ODUMPER_EXPORT
# fi 

NOW=`/bin/date +%Y%m%d-%H%M`

BACKUP_DIR="/home/admin/edge_exports/"

echo "${LIST_OF_INSIDE_IPADDRS}" | sed '/#/d; /^$/d' | while read ipv4addr login_user login_passwd edge_admin_port
do

	logit "Backup ${ipv4addr}:$edge_admin_port $login_user / $login_passwd"
	EDGE_NAME=""

	FILENAME=$BACKUP_DIR/edge_export-${ipv4addr}.cfg

	$wget --quiet --output-document=${FILENAME}	\
		--no-check-certificate --password ${login_passwd}	\
		--tries=2 --http-user=${login_user}			\
		--connect-timeout=4 -4					\
		https://${ipv4addr}:${edge_admin_port}/export

	case $? in
		0)	EDGE_NAME=`egrep 'set.*device.*hostname' ${FILENAME}  |
				sed 's/.*hostname //; s/ .*//'`
			logit "Saved config for ${EDGE_NAME:="unknown"} file as ${FILENAME}"
		;;  
		*)	FAILED_LIST="${FAILED_LIST} ${ipv4addr}"
			ERRORS=$(( ERRORS += 1 ))
			logit "error fetching export config with wget, please check. [ERRORS = $ERRORS]"
		;;  
	esac

	RCSFILE="${FILENAME},v"

	if [ ! -f "${RCSFILE}" ]; then
		logit "creating initial rcs file ... "
		echo "." | ci -i -u -m"initial backup made by by $0" ${FILENAME} 2>&1	| logit
	else
		logit "updating rcs file ... "
		$rcs -l "${FILENAME}"					2>&1		 | logit
		$ci  -m"automatic update by $0" "${FILENAME}"		2>&1		 | logit
	fi

	echo "ERRORS=\"$ERRORS\"; FAILED_LIST=\"$FAILED_LIST\"" > $TMPFILE

done

. $TMPFILE	

/bin/rm $TMPFILE

logit "Errors: $ERRORS. No backup for ${FAILED_LIST}"

exit $ERRORS

#
# Documentation and  standard disclaimar
#
# Copyright (C) 2011 Niels Thomas Haugård
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
#	edge_backup.sh 1
# SUMMARY
#	create RCS based archives for edge configurations
# PACKAGE
#	UNItools
# SYNOPSIS
#	edge_backup.sh [-v]
# DESCRIPTION
#	\fCedge_backup.sh(1)\fR is a poor mans backup program for SofaWare edge
#	Appliances managed through a service centre.
#
#	\fCedge_backup.sh(1)\fR is intented to run periodically from \fCcron(1)\fR
#	on the \fIservice centre\fR which also might host the \fImanagemet
#	center\fR. The \fIinternal IP address\fR of the edge is reachable
#	through the VPN tunnel.
#
#	The script is intented to run from \fCcron(1)\fR as the user \fCadmin\fR
#	on the \fIservice center\fR.
#
#	The recommended \fCcrontab(5)\fR is shown below:
# .nf \fC
# minutes  hours  day-of-month  month  day-of-week command
00 7-23 * * * /var/opt/UNItools/bin/edge_backup.sh >/dev/null 2>&
#           .fi \fP
#
# OPTIONS
# .IP \fC-v\fR
#	Print diagnostic output to STDOUT.
# FILES
#	The config file should be located in \fC$HOME/etc/edge_backup.cfg\fR.
#	The config file is a shell script containing one variable:
# .nf \fC

 LIST_OF_INSIDE_IPADDRS="
 #
 # carefull here be dragons
 #
 # ipv4addr	login_user	login_passwd	edge_admin_port
 #
 172.28.11.1	admin		1qazxsw2	981
 "

# .fi \fP
#	The format is shown above. Blank lines and linies beginning with
#	\fC#\fR are ignored.
# COMMANDS
#	\fCbash(1)\fR, \fCsed(1)\fR, \fCwget(1)\fR, etc.
# SEE ALSO
#	The Wiki at http://info.ssi.uni-c.dk.
# DIAGNOSTICS
#	Diagnostic putput is written to syslog. No further information
#	is provided in case of error(s).
# KNOWN BUGS AND LIMITATIONS
#	IP addresses for edge appliances must be maintained both in the
#	object database and the configuration file.
# VERSION
#      $Date: 2011/09/07 11:27:54 $
# .br
#      $Revision: 1.2 $
# .br
#      $Source: /lan/ssi/projects/UNItools/src/SPLAT/NGX/pkgs/edge_backup/edge_backup-1.0/edge_backup.sh,v $
# .br
#      $State: Exp $
# HISTORY
#	See rlog $Source: /lan/ssi/projects/UNItools/src/SPLAT/NGX/pkgs/edge_backup/edge_backup-1.0/edge_backup.sh,v $
# AUTHOR(S)
#	Niels Thomas Haugård
# .br
#	E-mail: niels.thomas.haugaard@uni-c.dk
# .br
#	UNI\(buC
# .br
#	Professional Security and Service
# .br
#	Danish Technical University, bldg 304
# .br
#	DK-2800 Lyngby, Denmark
#--
__DATA__

################################################################################
# edge backup
# minutes  hours  day-of-month  month  day-of-week command
00         7-23   *             *      *           /var/opt/UNItools/bin/edge_backup.sh >/dev/null 2>&1

################################################################################
#
# Ad-hoc edge backup for sa.dk
#
# The edge box'es are located behind NAT devices, but the inside address is accessible
# through the VPN tunnel, as it is part of the encryption domain.
#
# The list of edge which will be backed up by the script is maintained here:

LIST_OF_INSIDE_IPADDRS="
#
# carefull here be dragons
#
# ipv4addr	login_user	login_passwd	edge_admin_port
#
172.28.11.1	admin		1qazxsw2	981
172.28.5.1	admin		1qazxsw2	981
172.28.13.1	admin		1qazxsw2	981
172.28.14.1	admin		1qazxsw2	981
172.28.9.1	admin		1qazxsw2	981
172.28.12.1	admin		1qazxsw2	981
172.28.7.1	admin		1qazxsw2	981
172.28.6.1	admin		1qazxsw2	981
172.28.10.1	admin		1qazxsw2	981
172.28.8.1	admin		1qazxsw2	981
172.28.4.1	admin		1qazxsw2	981
"

#
# Notify anyone in case of errors ?
#
################################################################################
