#! /bin/bash
#
# $Header: /root/personal/nth/pkgs/fwbu/fwbu/RCS/UNIcpfwbu.sh,v 1.4 2013/06/27 10:39:40 root Exp $
#
# This is a wrapper for the OS specific backup procedure on Secure
# platform.
#
# The script builds restore information,  adds extra files to the
# backup (see list) and removes old archives.
#
# The restore information is written to RESTORE_INFORMATION in the
# directory where the system backup ususlly write its stuff
#
##################################################################
#
# Vars
#
##################################################################

TMPFILE=/var/tmp/backup_cmd_output.tmp

HOME=`awk -F: '$1 == "root" { print $6 }' /etc/passwd`

ME=`basename $0`			# script name
MY_LOGFILE=/var/log/backup.log		# my logfile. Will be mail'ed in case of errors

NOW=`date '+%Y%m%d-%H%M%S'`		# date YYYYmmdd-HHMMSS
HOSTNAME=`/bin/hostname`		# caliban.ssi.uni-c.dk / scan / ...
DOMAINNAME=`/bin/domainname`		# sik / ssi.uni-c.dk / ...

case $DOMAINNAME in
	""|\(none\))
		DNSDOMAIN=""		# fqdn may be identical to hostname
	;;
	*)	DNSDOMAIN=".${DOMAINNAME}"
	;;
esac

FQDN="`/bin/hostname`${DNSDOMAIN}"

OS=`uname -s`				# FreeBSD
VERSION=`uname -r`			# 5.2.1-RELEASE

BACKUP_SUCCEDDED_OK=0				# default: no errors on start
export BACKUP_SUCCEDDED_OK

# Place generic restore info here
# RESTORE_INFO_DIR=${HOME}/RESTORE_INFORMATION
RESTORE_INFO_DIR=/var/CPbackup/RESTORE_INFORMATION

# Keep this number of old backup files locally
BACKLOG=10

CFG=/var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg

##################################################################
#
# Dummy Functions - see CFG for OS specific
#
##################################################################

function do_system_backup()
{
 	:
}

function write_restore_procedure() {
	:
}

function do_pre_backup() {
	:
}

function add_files_to_backup_config() {
	:
}

function do_post_backup() {
	:
}

function rm_old_archives {
	:
}

function logit() {
# purpose     : Timestamp output
# arguments   : Line og stream
# return value: None
# see also    :
	LOGIT_NOW="`date '+%H:%M:%S (%d/%m)'`"
	STRING="$*"

	if [ -n "${STRING}" ]; then
		$echo "${LOGIT_NOW} ${STRING}" >> ${MY_LOGFILE}
		if [ "${VERBOSE}" = "TRUE" ]; then
			$echo "${LOGIT_NOW} ${STRING}"
		fi
	else
		while read LINE
		do
			if [ -n "${LINE}" ]; then
				$echo "${LOGIT_NOW} ${LINE}" >> ${MY_LOGFILE}
				if [ "${VERBOSE}" = "TRUE" ]; then
					$echo "${LOGIT_NOW} ${LINE}"
				fi
			else
				$echo "" >> ${MY_LOGFILE}
			fi
		done
	fi
}

function usage() {
# purpose     : Script usage
# arguments   : none
# return value: none
# see also    :
cat << EOF

	ERROR: $*

	Usage: `basename $0` [-v] [-c configfile] [-f filelist]

	Usage: `basename $0`

EOF
	exit 2
}

function clean_f () {
# purpose     : Clean-up on trapping (signal)
# arguments   : None
# return value: None
# see also    :
	$echo trapped
	exit 1
}

################################################################################
# Main
################################################################################
#
# clean up on trap(s)
#
trap clean_f 1 2 3 13 15

#
# Suppressing newline
#
echo="builtin echo "
case ${N}$C in
	"") if $echo "\c" | grep c >/dev/null 2>&1; then
		N='-n'
	else
		C='\c'
	fi ;;
esac

MY_ARGV=$*

#
# Process arguments
#
while getopts vc:f:h opt
do
case $opt in
	v)	VERBOSE=TRUE
	;;
	c)	CFG=$OPTARG
	;;
	f)	FILELIST=$OPTARG
	;;
	h)	usage
	;;
	*)	usage
	;;
esac
done
shift `expr $OPTIND - 1`

/bin/rm -f ${MY_LOGFILE} ${TMPFILE}

logit "Starting ${ME} ${MY_ARGV} and deleting old logfile '${MY_LOGFILE}'"

for RC in /etc/profile /etc/bashrc ${HOME}/.profile ${HOME}/.bash_login ${HOME}/.bashrc /opt/CPshared/5.0/tmp/.CPprofile.sh /tmp/.CPprofile.sh
do
	if [ -f "${RC}" ]; then
		logit "found rc file '$RC' sourcing it:"
		source "${RC}" # 2>&1 | logit
		logit "FWDIR=$FWDIR"
		logit "CPDIR=$CPDIR"
	fi
done

source ${CFG} || {
    echo "'${CFG}' not found, bye"
        exit 1
}
logit "loaded ${CFG} ... "

logit "Starting ... "

logit "PATH=$PATH"

logit "FWDIR=$FWDIR"

logit "Executing pre_backup ... "
do_pre_backup 2>&1 | logit

logit "Executing backup ... "
do_system_backup

logit "Executing do_post_backup ..."
do_post_backup

logit "Executing rm_old_archives ..."
rm_old_archives

exit 0

#
# Documentation and  standard disclaimar
#
# Copyright (C) 2012 Niels Thomas Haugård
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
#	UNIfwbu.sh 1
# SUMMARY
#	Wrapper for Check Point backup
# PACKAGE
#	UNItools
# SYNOPSIS
#	UNIfwbu.sh [-v]
# DESCRIPTION
#	Simple wrapper for Check Point backup on Secure Platform R65
#	and beyond. Tested on R75.
#
#	Creates /var/CPbackup/RESTORE_INFORMATION with a number of
#	documents describing the hardware, installed software and
#	version(s) and builds a restore procedure (README file).
#
#	The script add a number of files to the Check Point backup
#	procedure.
#
#	The script \fCUNIfwbu.sh(1)\fR preserves the backup procedure
#	configuration file as \fCsystem_configuration.cpbak.org\fR
#	in the same directory as the current configuration file.
#
#	\fCUNIfwbu.sh(1)\fR is installed as part of the package
#	\fBUNItools\fR.
#	
# OPTIONS
# .TP
#	\fC-v\fR
#	Verbose - print diagnostic output to the screen.
# COMMANDS
#	\fCbash(1)\fR, \fCsed(1)\fR, \fCawk(1)\fR and \fCbackup<fR.
# SEE ALSO
#	Documentation for UNItools and Check Point backup
# DIAGNOSTICS
#	None.
# BUGS
#	The Check Point backup fails if it detects that the CPMI process
#	is running.  Please close all GUI clients before backup.
# VERSION
#	$Date: 2013/06/27 10:39:40 $
# .br
#	$Revision: 1.4 $
# .br
#	$Source: /root/personal/nth/pkgs/fwbu/fwbu/RCS/UNIcpfwbu.sh,v $
# .br
#	$State: Exp $
# HISTORY
#	See \fCrlog\fR $Id$
# AUTHOR(S)
#	Niels Thomas Haugård
# .br
#	E-mail: thomas@haugaard.net
# .br
#	UNI\(buC
# .br
#	DTU, Building 304
# .br
#	DK-2800 Kgs. Lyngby
#--
