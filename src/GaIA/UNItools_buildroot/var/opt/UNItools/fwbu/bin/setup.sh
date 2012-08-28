#! /bin/sh
#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/fwbu/fwbu/RCS/setup.sh,v 1.4 2013/05/03 05:30:26 root Exp $
#

# install
# GAiA: Use /etc/cron.d/ instead of crontab
#
function f_install_etc_cron_d()
{
	if [ -d /etc/cron.d ]; then

		cat << EOF > /etc/cron.d/UNItools_backup
# periodic firewall backup
40 7 * * * root /var/opt/UNItools/fwbu/bin/UNIcpfwbu.sh
EOF
		chmod 644 /etc/cron.d/UNItools_backup

		/etc/init.d/crond restart

	else

		echo "/etc/cron.d not found/not a dir, bye"
		exit 1
	fi
}

function f_uninstall_etc_cron_d()
{
	echo removing /etc/cron.d/UNItools_backup ...
	/bin/rm -f /etc/cron.d/UNItools_backup
	/etc/init.d/crond restart
	exit 0
}

function f_install_crontab()
{
	echo old crontab:
	crontab -l | sed '/^#/d'
	(
		crontab -l | sed '/^#/d; /UNIcpfwbu/d; /backup/d'
		echo "0 0 * * 1,2,3,4,5,6,7 /var/opt/UNItools/fwbu/bin/UNIcpfwbu.sh"
	) | crontab 
	echo new crontab:
	crontab -l | sed '/^#/d'
}


function f_uninstall_crontab()
{
	echo old crontab:
	crontab -l | sed '/^#/d'
	(
		crontab -l | sed '/^#/d; /UNIcpfwbu/d; /backup/d'
		echo "0 0 * * 1,2,3,4,5,6,7 backup_util sched"
		echo "0 1 * * 1,2,3,4,5,6,7 /bin/echo y | /bin/backup -p 10"
	) | crontab 
	echo new crontab:
	crontab -l | sed '/^#/d'
}

VER=`fw ver 2>&1 | sed '/^This is/!d; s/.*R/R/; s/[ ]*-.*//; s/\.[0-9]*$//'`

case $VER in
	R75)	echo "installing in crontab for root ... "
	;;
	R76)	echo "installing in /etc/cron.d/ ... "
	;;
	*)	echo "fw version '$VER' unknown, bye"
		exit 1
	;;
esac

case $1 in
	install)
	case $VER in
		R75) f_install_crontab
		;;
		R76) f_install_etc_cron_d
		;;
	esac

	;;
	uninstall)
	case $VER in
		R75) f_uninstall_crontab
		;;
		R76)
		;;
	esac


	;;
	*)
	echo "usage: $0 install|uninstall"
	exit
	;;
esac

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
#	setup.sh 1
# SUMMARY
#	installation script for UNIfwbu.sh
# PACKAGE
#	UNItools
# SYNOPSIS
#	setup.sh install | uninstall
# DESCRIPTION
#	Simple installation routine for \fCUNIfwbu.sh(1)\fR removing
#	prev. cron entries related to check point backups adding 
#	backup with \fCUNIfwbu.sh(1)\fR.
#	
#	The uninstall procedure reverces the process - but does not
#	alter the check point backup procedure configuration file.
#
#	The script \fCUNIfwbu.sh(1)\fR preserves the backup procedure
#	configuration file as \fCsystem_configuration.cpbak.org\fR
#	in the same directory as the current configuration file.
#
#	\fCUNIfwbu.sh(1)\fR is installed as part of the package
#	\fBUNItools\fR.
#	
# OPTIONS
#	None.
# COMMANDS
#	\fCbash(1)\fR, \fCcrontab(1)\fR
# SEE ALSO
#	Documentation for UNItools and Check Point backup
# DIAGNOSTICS
#	None.
# BUGS
#	None known.
# VERSION
#	$Date: 2013/05/03 05:30:26 $
# .br
#	$Revision: 1.4 $
# .br
#	$Source: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/fwbu/fwbu/RCS/setup.sh,v $
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
