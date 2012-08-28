


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
#	UNIfwbu.sh 1
# SUMMARY
#	rsync baseret firewall(1) backup
# PACKAGE
#	UNIbackup
# SYNOPSIS
#	UNIfwbu.sh [-v] \fIkonfigurationsfil\fR
# BESKRIVELSE
#	\fCUNIfwbu.sh(1)\fR anvendes til at hente system status,
#	firewall og operativsystems konfigurationsfiler tilbage til
#	sikkerhedsafdelingen, til brug ved en katastrofe reetablering.
#
#	Systemet foruds�tter, at pakken \fBUNItools\fR er installeret
#	p� firewall'en.
#
#	\fCUNIfwbu.sh(1)\fR udf�res periodisk via \fCcron(1)\fR, og
#	startes af \fCUNIrun_fwbu.sh(1)\fR.
#
#	\fCUNIfwbu.sh(1)\fR bruger \fCrsync(1)\fR over \fCssh(1)\fR
#	til at lave dels
# .IP o
#	et dokument med den �jeblikkelige \fIsystem status\fR,
# .IP o
#	en sikkerhedskopi af de �jeblikkelige konfigurationsfiler
#	for firewall og operativsystem,
# .IP o
#	en lokal sikkerhedskopi af den daglige backup af
#	firewall'ens konfigurationsfiler.
#
#	Det er planlagt senere automatisk at flytte dokumenterne ind i
#	et CVS tr�, samt at lave versionskontrol og automatisk 
#	opdatering af kundens dokumentation p� baggrund af opdagede
#	�ndringer.
#
#	Der anvendes et operativsystem specifikt script til at
#	lave system status. Disse scripts ligger i \fC/var/opt/UNIfwbu/etc\fR,
#	og kopieres ud p� firewall'en, udf�res og slettes. De
#	efterlader fire dokumenter i hjemmekataloget for den bruger
#	der anvendes ved login, og dokumenterne flyttes efterf�lgende til
#	log kataloget og de gemmes i �n generation:
# .RS
# .TP
#	\fC$HOME/current_system_status\fR
#	System status information (output fra bl.a. \fCnetstat\fR, \fCifconfig\fR,
#	\fCfw stat\fR, osv.)
# .TP
#	\fC$HOME/current_statistical_information\fR
#	Volatil system statistisk information.
#	\fCfw stat\fR, osv.)
# .TP
#	\fC$HOME/.all_files\fR
#	Alle dokumenter der skal tages backup af. Links er resolverede, og 
#	\fC$FWDIR\fR er fundet (�ndres med hver opgradering/patching).
#	Dokumentet skal senere danne udgangspunkt for \fCCVS\fR \fCadd\fR og
#	\fCremove\fR kommandoer.
# .TP
#	\fC$HOME/.backup_files\fR
#	Alle dokumenter p� et format hensigtsm�ssig som argument til \fRrsync(1)\fR.
#	Dette format g�r, at filnavne med mellemrum ikke er tilladte.
#
# .RE
#	
# OPTIONS
# .TP
#	\fC-v\fR
#	Verbose; skriv til stdout samt til logfil.
# .TP
#	\fIkonfigurationsfil\fR
#	En kunde kan have mange maskiner der skal tages backup af.
#	Firewall(s), reservemaskiner, snortlogs osv. og der er derfor
#	n�dvendigt at kunne h�ndtere en �n kunde til mange maskiner
#	relation.
#	
#	Konfigurationsfil og dokunenter til en specifik kundes
#	maskine(r) ligger under \fC/lan/ssi/\fIkundenavn\fC/hosts\fR.
#	Her er for hver maskine et katalog (maskinens navn) samt
#	et konfigurationsdokument, der skal hedde det samme med
#	extension \fC.conf\fR, f.eks. \fCdefgw.conf\fR.
#
# KONFIGURATIONSFIL
#	Syntaksen er \fIvariabel\fC = \fIv�rdi\fR. Dokumentet
#	processeres af \fCawk(1)\fR og resultatet sources af
#	\fCbash(1)\fR - s� pas p� med syntaksen!
#
#	Dokumentet skal indeholde f�lgende:
# .nf
#	\fC
    1	# Kundens dom�nenavn -- katalog i /lan/ssi
    2	DOMAIN_NAME = ssi.uni-c.dk
    3	
    4	# navn p� maskinen -- det bliver ogs� et katalognavn
    5	HOST_NAME   = defgw
    6	
    7	# maskinens IP -- hertil laves ssh forbindelsen
    8	IP      = 172.16.0.1
    9	
   10	# Hvilken port ssh er bundet til
   11	SSH_PORT    = 22
   12	
   13	# Login p� maskinen (som root) med denne bruger
   14	LOGIN_USER  = admin
   15	
   16	# OS version (SunOS IPSO Linux ... )
   17	UNAME_MAJOR = SunOS
   18	
   19	# OS version version (2.6 3.7 6.3 ... )
   20	UNAME_MINOR = 2.6
   21	
   22	# Hvilken firewall type (FW1  OSFW)
   23	FW_TYPE     = FW1
   24	
   25	# Hvilken firewall version (4.0 4.1 NG ... )
   26	FW_VER      = 4.1
   27	
   28	# belast denne RCPT med fejlpost
   29	RCPT        = fwsupport@uni-c.dk
   30	
   31	# Er deslogin instaleret - og p� hvilken port (NONE 22 30 ... )
   32	DESLOGIN_PORT   = 30
   33	
   34	# Nick names (til ssh /td) for denne host ud over HOST_NAME
   35	NICK_NAMES  = ssi
   36	
   37	# Ekstra kundespecifikke filer
   38	EXTRA_FILES = 
# .fi
#	\fR
#	Alle variable er obligatoriske, med undtagelse af \fCEXTRA_FILES\fR,
#	\fCNICK_NAMES\fR samt \fCDESLOGIN_PORT\fR.
#
#	Har kunden nogle specielle ekstra dokumenter der skal med p� en
#	backup, anf�res de i \fCEXTRA_FILES\fR, f.eks. \fC/var/ace\fR.
#
#	Hvis kunden har noget installeret (f.eks. en ACE server) der kr�ver
#	en bestemt kommando udf�rt, for at danne et dokument der skal p�
#	backup, skal det ske p� maskinen selv, f.eks. i forbindelse med
#	den daglige backup. Husk i den forbindelse at angive dette specielle
#	script i \fCEXTRA_FILES\fR, s� det kommer med p� backup'en :-)
# COMMANDS
#	\fCsh(1)\fR, \fCssh(1)\fR, \fCrsync(1)\fR, \fCsed(1)\fR og \fCawk(1)\fR.
# SE OGS�
#	Dokumentationen for UNIbackup.
# DIAGNOSTICS
#	Fejler programmet sendes en e-mail til den i konfigurationsfilen
#	anf�rte adresse.
# BUGS
#	Det er der sikkert. Der er bl.a. en fejl omkring etablering af
#	ssh forbindelsen, hvis firewall'ens n�gler er blevet �ndret kr�ver
#	det en operat�r indgriben; jeg g�tter p�, at processen vil h�nge
#	for tid og evighed.
#
#	\fCrsync(1)\fR f�r alle filnavne p� kommandolinien som argumentet
#	\fC`cat .all_files`\fR. Det betyder, at der ikke m� findes filnavne
#	med blank-tegn, samt at der er en operativsystem specifik gr�nse for,
#	hvor stort dette argument m� v�re.
# VERSION
#	$Date: 2003/08/13 13:40:31 $
# .br
#	$Revision: 1.17 $
# .br
#	$Source: /lan/ssi/projects/UNIfwbu/src/RCS/UNIfwbu.sh,v $
# .br
#	$State: Exp $
# HISTORY
#	Se \fCrlog\fR $Id$
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
