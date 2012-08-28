#!/bin/sh
# 
#
#                                      Tue Mar 18 15:56:20 CET 2014
# Preample
# --------
# This script is the documentation for how atop 2.0.2 was downloaded,
# configured, compiled and installed as part of the pkg-package UNItools
# for use in a Check Point GaIA environment.
# 
# The link ''setup.sh'' is executed during the update of all programs
# in UNItools. You are required to link it to the correct version of
# setup*.sh
# 
# All programs, README etc. ends up below /var/opt/UNItools. No man
# pages, unused libs or include files. All other files must be created
# as part of the setup script for UNItools.
# 
# All binary programs:		/var/opt/UNItools/bin
# All configuration files:	/var/opt/UNItools/etc/atop
# All relevant documentation:	/var/opt/UNItools/docs/atop.2.0.2
# 
# Un-comment out the relevant commands to build the package.
# 
# Installation receipt
# --------------------
# Change to the working directory created by pkg_setup:
# cd /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/atop
# 
#  1	Download the package atop, and read the package documentation,
# 	usually README and INSTALL.
# 
# 	wget -N http://www.atconsultancy.nl/atop/packages/atop-1.19.tar.gz
# 
# 	/bin/gtar xvzf atop-1.19.tar.gz
#	
#	Notice that atop 2.0.2 does not work in GaIA.
# 
#  2	Change the values below so they describe how the package has
# 	to be compiled and installed (configure and make), any start/
# 	stop scripts and NAME anv VENDOR. The info is saved in
# 	/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/CFG
# 
cat << "END_OF_CFG" > CFG
URL="http://www.atconsultancy.nl/atop/packages/atop-1.19.tar.gz"
PKG="atop"
VER="1.19"
NAME="AT Computing's System & Process Monitor"
VENDOR="Gerlof Langeveld, AT Computing, Nijmegen, The Netherlands, gerlof@ATComputing.nl"
SRC="atop-1.19"
ROOT="/var/opt/UNItools"
CONFIGURE="/bin/echo no configure "
BUILD="make"
INSTALL="make install"
INSTALL_MORE="/bin/sh install_more.sh"
MAKECLEAN="make distclean"
DELEFILES="*.bak"
END_OF_CFG
# 
#  3	Compile the package and create a temporary installation. If some
# 	of the applications needs to be created static then it *may* be
# 	required to set the env. var LDFLAGS=-static

export LDFLAGS=-static

#	Change on-the-fly Makefile, man pages and 'rawlog.c' so logfile paths 
#	reads from below /var/opt/UNItools not somewhere else
# 
	if [ ! -f atop-1.19/Makefile.dist ]; then
		cp atop-1.19/Makefile atop-1.19/Makefile.dist
	fi
	sed "
		s%^LDFLAGS.*%LDFLAGS = -lncurses -lm -lz -static%
		s%^DESTDIR.*%DESTDIR = /var/opt/UNItools% 
		s%^BINPATH.*%BINPATH = /bin%g
		s%^LOGPATH.*%LOGPATH = /log/atop%g
		s%^MANPATH.*%MANPATH = /share/man/man1%
	" atop-1.19/Makefile.dist > atop-1.19/Makefile

	for f in atop.24hours atop.cron atop.daily atop.init
	do
		if [ ! -f atop-1.19/$f.dist ]; then
			cp atop-1.19/$f atop-1.19/$f.dist
		fi
		sed "
		s%/var/log/atop%/var/opt/UNItools/log/atop%
		s%/usr/bin%/var/opt/UNItools/bin%
		s%/etc/atop/atop.daily%/var/opt/UNItools//etc/atop/atop.daily%
		" atop-1.19/$f.dist > atop-1.19/$f
		# diff atop-1.19/$f.dist atop-1.19/$f
	done

	if [ ! -f atop-1.19/man/atop.1.dist ]; then
		cp atop-1.19/man/atop.1 atop-1.19/man/atop.1.dist
	fi
	sed 's%/var/log/atop%/var/opt/UNItools/log/atop"%' atop-1.19/man/atop.1.dist > atop-1.19/man/atop.1

	if [ ! -f atop-1.19/rawlog.c.dist ]; then
		cp atop-1.19/rawlog.c atop-1.19/rawlog.c.dist
	fi
	sed 's%^define.*BASEPATH.*%#define BASEPATH	"/var/opt/UNItools/log/atop/"%' atop-1.19/rawlog.c.dist > atop-1.19/rawlog.c

#
#	... and the init script - atop.init - must be changed too:
#
#
	cp ./atop.init.uni-c atop-1.19/atop.init

 	pkg_conbat -n ./CFG

# 	will build and install it temporarely in /var/opt/UNItools (which
# 	will be moved during the installation). A script for testing will
# 	also be produced. Use '-n' to avoid prompting for the renaming of
# 	/var/opt/UNItools
# 	If atop requires something else to compile, please correct the
# 	section that writes to CFG.
# 	The new files are then moved to atop.2.0.2.install.tmp - which
# 	will be wiped first.
# 	Copy extra files with ''install_more'' which sould add the files
# 	to /var/opt/UNItools/ ...
# 
# 	If atop requires a start/stop script, then it will have to be made
# 	some where else and installed with /var/opt/UNItools/bin/setup.sh
# 
# 	The successful output of pkg_conbat is a test-archive for testing
# 	atop on a firewall.
# 
#  4	Test the archive according to the putput from pkg_conbat. The test
#  	script checks for existing files (noclobber), and missing shared
# 	libraries. Remove the files from the firewall afterwards.
# 
#  5	If everything is OK then add the package to /var/opt/UNItools with
# 	the command
# 
 	pkg_install.sh ./CFG
# 
# 	Remember to run pkg_conbat first.
# 
#  6	Finally clean up used space with
# 
# 	pkg_clean.sh ./CFG
# 
# 	which will delete all temporary files and install archives but not
# 	the original downloaded source.
# 
# If /var/opt/UNItools gets poluted with unwanted stuff, you may do a clean
# install of everything with
# 
# 	pkg_do_it_all_for_all_known_packages
# 
#  7  Finally make a new Linux PKG version of UNItools
# 
# Final note
# ----------
# This is a script. It was made with the command:
# 
# pkg_setup http://www.atoptool.nl/download/atop-2.0.2.tar.gz 2.0.2 atop
# 
