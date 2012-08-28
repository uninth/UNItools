#!/bin/sh
#
# $Header: /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/src/scripts/RCS/UNIfwbu.sh,v 1.7 2005/09/27 12:36:44 root Exp $
#
# Linux and NG only !
#

#
# Gem dette antal backup arkiver ad gangen. Antallet
# svarer til et arkiv pr. dag. Hvert arkiv fylder ca
# 1Mb.
#
BACKLOG=10

# Tidsstempel, hostnavn og domænenavn til logfil
TIMESTAMP=`/bin/date +%Y%m%d-%H%M%S`
HOSTNAME=`/bin/hostname`
DOMAINNAME=`/bin/domainname`

# Navn på backup arkivet 
ARCHIVE="${HOSTNAME}.${DOMAINNAME}.${TIMESTAMP}"

# Scriptnavn og lokation
ME="`/bin/basename $0 .sh`"
MYDIR=/var/opt/UNItools/

# Den egentlige backup kommando; en modifikation
# af check points script, hvor der ikke afbrydes
# hvis firewall-1 kører.
BACKUP_CMD="${MYDIR}/bin/backup_start_UNIC"
BACKUP_ARGS="all "
ARCHIVE_LIST=archive_list

# Scriptets logfil; den overskrives hver gang, men
# skrives til syslog med logger ved afslutning.
MY_LOGFILE=/var/log/backup.log

# Flag til indikation af eventuelle fejl (variable overlever ikke () )
ERRORS=/tmp/.err.$$

/bin/rm -f $ERRORS

#
# Funktioner
#
logit() {
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


#
# MAIN
#

if [ "${1}" = "-v" ]; then
	VERBOSE="TRUE"
else
	VERBOSE="FALSE"
fi

echo=/bin/echo
case ${N}$C in
        "") if $echo "\c" | grep c >/dev/null 2>&1; then
                N='-n'
        else
                C='\c'
        fi ;;
esac

#
# Slet logfilen
#
/bin/rm -f ${MY_LOGFILE}

#
# Fortæl fortæl
#
logger -p mail.crit "exec $0 $*"

logit "Påbegynder daglig backup af ${HOSTNAME}.${DOMAINNAME}"
logit "Beholder maksimalt ${BACKLOG} gamle sikkerhedskopier"

logit "Sætter environment - sourcer ~/.profile | ~/.bash_profile og ~/.bashrc "
logit "\$HOME = $HOME - "
case `uname` in
        IPSO)   logit "$0 virker ikke under IPSO"
		logit "Konfigurer istedet backup fra Voyager"
		exit 1
        ;;
        Linux|Solaris) logit "Linux/Solaris: sourcer $HOME/.profile ... "
		. $HOME/.bash_profile 2>&1	| logit
		. $HOME/.bashrc 2>&1		| logit
        ;;
        *)	logit "Andet: sourcer $HOME/.profile ... "
		. $HOME/.profile 2>&1		| logit
        ;;
esac

# i tilfælde af fejl ...
SMTPCLIENT=/var/opt/UNItools/bin/smtpclient
if [ ! -x $SMTPCLIENT ]; then
	STR="smtp client '$SMTPCLIENT' kan ikke udføres"
	logit "$STR"
	logger -p mail.crit "$STR"
	exit 1
fi

SMTPCFG="/var/opt/UNItools/conf/smtpclient.SH"
if [ -f $SMTPCFG ]; then
	.	$SMTPCFG
	logit "I tilfælde af fejl, sendes en e-mail på denne måde:"
	logit "smtp client: '$SMTPCLIENT'"
	logit "Argumenter:  '$OPTIONS'"
else
	STR="Konfigurationsdokumentet '$SMTPCFG' findes ikke"
	logit "$STR"
	logger -p mail.crit "$STR"
	exit 1

fi

if [ -x "${BACKUP_CMD}" ];
then
	(
		echo "starter ${BACKUP_CMD} ${BACKUP_ARGS} ${ARCHIVE} "
		${BACKUP_CMD} ${BACKUP_ARGS} ${ARCHIVE}
		echo "exit status $?"
		echo "afsluttet backup"

	) 2>&1 | logit

	logit "Validering af backup. Firewall-1 blev ikke stoppet før kopieringen startede"

	TMPDIR=/opt/CPbackups/tmp.${TIMESTAMP}.$$

	ARCHIVE=${ARCHIVE}.tgz

	mkdir ${TMPDIR}

	cd ${TMPDIR}
	
	gunzip=/bin/gunzip
	$gunzip -c ../${ARCHIVE} | tar xfp - | logit

	logit "Sammenligner filer i / med ${TMPDIR}"

	/usr/bin/find . -follow -type f | while read FILE
	do
		if [ -n "${FILE}" -a -f "/${FILE}" ]; then
			#
			# Filen må ikke være tom, men kan godt være rettet
			#
			ORG=`/usr/bin/sum -r 	"${FILE}" | awk '{ print $1 }'`
			CPY=`/usr/bin/sum -r	"/${FILE}" | awk '{ print $1 }'`
			if [ "${ORG}" -ne "${CPY}" ]; then
				STR="Advarsel: størrelsen ændret i ${FILE} (fra '${ORG}' til '${CPY}'"
				echo $STR | logit
				/bin/ls -l ${FILE} /${FILE} | logit 
				echo $STR >> $ERRORS
				/bin/ls -l ${FILE} /${FILE} >> $ERRORS
			fi
		else
			if [ "${FILE}" != "./opt/CPbackups/signature" ]; then
				STR="Filen ${FILE} findes på arkivet, men ikke i filsystemet"
				logit $STR
				echo		>> $ERRORS
				echo $STR	>> $ERRORS
			fi
		fi
	done

	logit "Backup indeholder disse filer mv.:"
	/usr/bin/find . -follow 2>&1 | logit

	cd ..

	logit "Sammenligning færdig. Sletter det temporære katalog ${TMPDIR}"
	/bin/rm -fr ${TMPDIR}

	logit "Roterer gamle sikkerhedskopier ... "
	/usr/bin/md5sum ${ARCHIVE} >> ${ARCHIVE_LIST}

	while :;
	do
		LINES=`/usr/bin/wc -l < ${ARCHIVE_LIST} | /usr/bin/tr -d ' '`

		if [ ${LINES} -gt ${BACKLOG} ]; then
			DELE=`/bin/sed "s/.* //g; q" ${ARCHIVE_LIST}`
			logit "Sletter den gamle sikkerhedskopi '${DELE}'"
			/bin/rm -f ${DELE}
			/bin/grep -v "${DELE}" ${ARCHIVE_LIST} > ${ARCHIVE_LIST}.tmp
			/bin/mv ${ARCHIVE_LIST}.tmp ${ARCHIVE_LIST}
		else
			break
		fi
	done

else
	# Nope -- backupscriptet kan ikke udføres
	STR="backup scriptet '${BACKUP_CMD}' kan ikke udføres:"
	echo $STR logit 
	echo $STR >> $ERRORS
fi

cat ${MY_LOGFILE} | /usr/bin/logger -t ${ME} -p mail.crit

#
# Any errors ?
#
if [ ! -f ${ERRORS} ]; then
	logit "Daglig sikkerhedskopiering afsluttet korrekt"
	exit
else
	logit "Daglig sikkerhedskopiering indeholdt fejl"
fi

#
# Nope. Send mail to someone
#
. /var/opt/UNItools/conf/smtpclient.SH

/usr/bin/logger -t ${ME} -p mail.crit "sender mail til ${DEF_RCPT} om problemet"
(
date | awk '{ printf("\n%80s\n\n"), $0 }'

cat << EOF
Til ${DEF_RCPT}

Daglig backup gik galt på dette system:

Hostname:	${HOSTNAME}
Domainname:	${DOMAINNAME}

Fejl:
EOF

cat $ERRORS

cat << EOF

Fuld log følger herunder.

EOF

cat ${MY_LOGFILE}

echo
echo "Der findes følgende backup arkiver på maskinen:"
echo "Dokumenterne ligger i `pwd`."
echo

ls -l 

echo
echo "Backup systemet kender følgende af disse arkiver:"
echo

cat ${ARCHIVE_LIST}

cat << EOF

Jeg håber du hurtigt finder fejlen.

Venligst, $ME
--
EOF
echo '$Header: /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/src/scripts/RCS/UNIfwbu.sh,v 1.7 2005/09/27 12:36:44 root Exp $'


) | ${SMTPCLIENT} ${OPTIONS} -s "Fejl ved daglig backup af ${FQDN}"

/bin/rm -f $ERRORS

exit 0

################################################################################
#
# Documentation and  standard disclaimar
#
# Copyright (C) ECMWF
# http://www.ecmwf.int/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#

# Det huer mig ikke, at check points backup procedure insisterer på
# at firewal-1 skal være stoppet for at lave backup'en.
#
# I stedet for har jeg en svagt modificeret version af scriptet, der
# laver en identisk backup - uden check for, om firewall-1 er nede,
# og pakker efterfølgende tar arkivet ud og sammenligner (med diff)
# med de dokumenter, der skulle være taget en backup af.
#
# Tag backup. Kontroller den er identisk med de dokumenter, der ligger
# i filsystemet.
# send en mail til fwsupport, hvis det ikke er tilfældet.
#
# Slet gamle backup filer.

# I stedet for har jeg en svagt modificeret version af scriptet, der
# laver en identisk backup - uden check for, om firewall-1 er nede,
# og pakker efterfølgende tar arkivet ud og sammenligner (med diff)
# med de dokumenter, der skulle være taget en backup af.
#
# Tag backup. Kontroller den er identisk med de dokumenter, der ligger
# i filsystemet.
# send en mail til fwsupport, hvis det ikke er tilfældet.
#
# Slet gamle backup filer.
#
#
#++
# NAME
#	UNIfwbu.sh 1
# SUMMARY
#	Sikkerhedskopiering af en VPN / Appliance firewall-1
# PACKAGE
#	UNItools
# SYNOPSIS
#	\fBUNIfwbu.sh\fR 
# DESCRIPTION
#	\fCUNIfwbu.sh\fR kalder en svagt modificeret version af 
#	Check Points backup script, \fC/bin/backup_start\fR, der
#	laver en sikkerhedskopiering af system konfiguration og
#	firewall, til senere re-etablering med \fC/bin/restore_start\fR.
#
#	\fC/bin/backup_start\fR er rettet, så det kan udføres 
#	på trods af, at firewall-1 kører.
#
#	Den rettede udgave af scriptet (\fCbackup_start_UNIC\fR)
#	afvikles og skriver output til \fC/var/log/backup.log\fR.
#	Logfilen overskrives hver gang scriptet udføres.
#	
#	Efter backup, pakkes sikkerhedskopien (et \fCtar(1) arkiv\fR)
#	ud i et temporært katalog,
#	og dokumenterne sammenlignes med de oprindelige. Hvis der
#	er en forskel adviseres den ansvarlige senere via smtp.
#
#	Gamle arkiver slettes, så der kun er 10 arkiver	ad gangen.
#
#	SMTP adressen på den ansvarlige fås fra
#	\fC/var/opt/UNItools/conf/smtpclient.SH\fR.
#
#	Scriptet startes fra \fCcron(1)\fR en gang i døgnet.
#
# OPTIONS
#	Ingen.
# FILES
#	Der anvendes et konfigurationsdokument for at finde
#	den ansvarliges postadresse. Dokumentet er
#	\fC/var/opt/UNItools/conf/smtpclient.SH\fR.
# COMMANDS
#	\fCshell(1)\fR, \fCtar(1)\fR, \fCcron(1)\fR, og
#	\fC/bin/backup_start\fR.
# DIAGNOSTICS
#	I tilfælde af, at \fCdiff(1)\fR finder forskel mellem
#	dokumenter i sikkerhedskopien og i filsystemet, adviseres
#	den systemansvarlige via smtp.
# BUGS
#	Ingen kendte, men der undersøges ikke for, om firewall-1
#	konfigurationsfilerne er åbne via GUI'en; kun at de ikke
#	er rettede under backup.
# VERSION
#      $Date: 2005/09/27 12:36:44 $
# .br
#      $Revision: 1.7 $
# .br
#      $Source: /lan/ssi/projects/UNItools/src/Linux/2.4.21-20cpsmp/src/scripts/RCS/UNIfwbu.sh,v $
# .br
#      $State: Exp $
# HISTORY
#	Se \fCrlog UNIfwbu.sh\fR.
# AUTHOR(S)
#       Niels Thomas Haugård
# .br
#       E-mail: thomas@haugaard.net
# .br
#       UNI\(buC
# .br
#       DTU, Building 304
# .br
#       DK-2800 Kgs. Lyngby
#--
