#!/bin/sh
# 
#
#                                      Wed Mar 26 16:02:08 CET 2014
# Preample
# --------
# This script is the documentation for how ofiller 2.0 was downloaded,
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
# All configuration files:	/var/opt/UNItools/etc/ofiller
# All relevant documentation:	/var/opt/UNItools/docs/ofiller.2.0
# 
# Un-comment out the relevant commands to build the package.
# 
# Installation receipt
# --------------------
# Change to the working directory created by pkg_setup:
# cd /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/ofiller
# 
#  1	Download the package ofiller, and read the package documentation,
# 	usually README and INSTALL.
# 
# wget -N http://www.lindercentral.com/ofiller/ofiller_2.0.tgz
# 
# /bin/gtar xvzf ofiller_2.0.tgz
# 
#  2	Change the values below so they describe how the package has
# 	to be compiled and installed (configure and make), any start/
# 	stop scripts and NAME anv VENDOR. The info is saved in
# 	/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/CFG
# 
cat << "END_OF_CFG" > CFG
URL="http://www.lindercentral.com/ofiller/ofiller_2.0.tgz"
PKG="ofiller"
VER="2.0"
NAME="Object Filler and Object Dumper for Check Point"
VENDOR="Martin Hoz, (c) 2003-2005 by Check Point Software Technologies, Ltd. and subsidiaries"
SRC="ofiller_2.0"
ROOT="/var/opt/UNItools"
CONFIGURE="configure --prefix=/var/opt/UNItools --mandir=/var/opt/UNItools/share/man"
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
#     
# export LDFLAGS=-static
# 
# 	Ofiller is made with automake and configure then

	cp Makefile ofiller_2.0/Makefile
 
 	pkg_conbat -n ./CFG
# 
# 	will build and install it temporarely in /var/opt/UNItools (which
# 	will be moved during the installation). A script for testing will
# 	also be produced. Use '-n' to avoid prompting for the renaming of
# 	/var/opt/UNItools
# 	If ofiller requires something else to compile, please correct the
# 	section that writes to CFG.
# 	The new files are then moved to ofiller.2.0.install.tmp - which
# 	will be wiped first.
# 	Copy extra files with ''install_more'' which sould add the files
# 	to /var/opt/UNItools/ ...
# 
# 	If ofiller requires a start/stop script, then it will have to be made
# 	some where else and installed with /var/opt/UNItools/bin/setup.sh
# 
# 	The successful output of pkg_conbat is a test-archive for testing
# 	ofiller on a firewall.
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
# pkg_setup http://www.lindercentral.com/ofiller/ofiller_2.0.tgz 2.0 ofiller
# 
