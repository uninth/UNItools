#
# Documentation and  standard disclaimar
#
# Copyright (C) 2001 Niels Thomas Haugård
# ECMWF
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
#++
# NAME
#	rootvg_backup.pl 1
# SUMMARY
#	do mksysb/savevg on HDR
# PACKAGE
#	HDR Backup package
# SYNOPSIS
#	\fCrootvg_backup.pl\fR \fIoptions\fR
# DESCRIPTION
#	\fCrootvg_backup.pl\fR is a AIX backup script intented to run periodically
#	from \fCcron(1)\fR. It uses uses \fCmksysb(1)\fR to backup \fCrootvg\fR on
#	on all systems, and on the control workstation also \fCspdatavg\fR.
#
#	Backup is based on \fChostname(1)\fP, and done this way
# .TP
#	\fBControl Workstation\fP
#	backup of \fCrootvg\fP and \fCspdatavg\fP to a local tape 20Gb DDS4 drive.
#	This requires two tapes.
# .TP
#	\fBnodes\fP
#	Direct backup of \fCrootvg\fP to the \fIcontrol workstation\fR via NFS, and
#	ADSM. There should be no need for interaction.
# .TP
#	\fBstand alone systems\fP
#	Backup of \fCrootvg\fR to a local tape drive. One tape is required.
# .PP
#	Tapes are located in the firesafe of the DRS building.
#
#	The script is not intented to print anything to \fCstdout\fP, but redirects
#	all output to a logfile.
#
#	The script keeps an internal list to map \fIhostname\fP to a backup type.
#	The list need updating, as new hosts are beeing introduced, or hostnames
#	changes. Update the script on the control workstation, then distribute the
#	contents of \fC/rootvg_backup\fR to all nodes and stand alone systems, using
#	\fCpcp(1)\fP.
# OPTIONS
# .IP \fC--config\fR\ |\ \fC-c\fR\ \fIconfigfile\fR
#	Use \fIconfigfile\fR instead of the default \fC/rootvg_backup/etc/backup.conf\fR.
# .IP \fC--debug\fP\ |\ \fC-d\fP
#	Display aditional diagnostic output.
# .IP \fC--doit\fP\ |\ \fC-doit\fP\ |\ \fC-x\fP
#	Execute the backup.
# .PP
#	No args: test the backup with the default config file; do not execute
#	any commands.
# FILES
#	The config file has the following format - blank lines and lines
#	starting with \fC#\fP are ignored:
# .nf \fC
#
    1	#mydir  : root path for backup script and data.
    2	#bin    : path to scripts
    3	#utils  : path to derived scripts
    4	#logfile: path to the backup logfile
    5	#rcpt   : smtp addresse(s) of backup master
    6	#
    7	# DEFAULT VALUES:
    8	#
    9	mydir   : /rootvg_backup/
   10	bin     : /rootvg_backup/bin
   11	utils   : /rootvg_backup/utils
   12	logfile : /logfiles/backup.log
   13	rcpt    : syl@ecmwf.int,ibl@ecmwf.int,syy@ecmwf.int
#
# .fi \fP
# COMMANDS
#	\fCperl(1)\fR, \fCmksysb(1)\fR, \fCsavevg(1)\fR
# SEE ALSO
#	Documentation for the HDR Backup package
#	in \fC/rootvg_backup/documentation\fP.
# DIAGNOSTICS
#	Diagnostic output is printed to STDOUT, and STDERR. As the
#	script is inworked by \fCcron(1)\fP, this means that any
#	script errors will be sent by mail to \fCroot\fP.
# KNOWN BUGS AND LIMITATIONS
#	When killing the process, childprocesses are not killed.
#	Killing the process before \fCpost-backup\fP is run, will
#	require \fCpost-backup\fP to be run by hand.
# .br
#	The script \fCmk.utils(1)\fR which is executed from 
#	\fCrootvg_backup.pl\fR, has a work around for that problem.
#
#	This procedure need to be changed if file systems \fCrootvg\fR
#	or \fCspdatavg\fR on the control workstation  exceed  20Gb, as
#	this is the limit of the current tape drive.
#
#	The change is needed as \fCmksysb(1)\fC does not
#	work without a controlling tty when requesting aditional 
#	tape(s).
# VERSION
#      $Date: 2002/06/19 10:13:44 $
# .br
#      $Revision: 1.7 $
# .br
#      $Source: /rootvg_backup/bin/RCS/rootvg_backup.pl,v $
# .br
#      $State: Exp $
# HISTORY
#	See rlog $Source: /rootvg_backup/bin/RCS/rootvg_backup.pl,v $
# AUTHOR(S)
#	The script is based on previous work found on the \fCathos\fR node,
#	and other input. Assembled by
# .br
#	Niels Thomas Haugaard
# .br
#	E-mail: thomas@haugaard.net
# .br
#	ECMWF
# .br
#	Shinfield Park
# .br
#	Reading, Berks.
# .br
#	RG2 9AX  England
#--
