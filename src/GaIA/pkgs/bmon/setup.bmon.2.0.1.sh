#!/bin/sh
# 
#
#                                      Wed Mar 19 12:20:35 CET 2014
# Preample
# --------
# This script is the documentation for how bmon 2.0.1 was downloaded,
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
# All configuration files:	/var/opt/UNItools/etc/bmon
# All relevant documentation:	/var/opt/UNItools/docs/bmon.2.0.1
# 
# Un-comment out the relevant commands to build the package.
# 
# Installation receipt
# --------------------
# Change to the working directory created by pkg_setup:
# cd /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/bmon
# 
#  1	Download the package bmon, and read the package documentation,
# 	usually README and INSTALL.
# 
# wget -N http://www.carisma.slowglass.com/~tgr/bmon/files/bmon-2.0.1.tar.gz
# 
# /bin/gtar xvzf bmon-2.0.1.tar.gz
# 
#  2	Change the values below so they describe how the package has
# 	to be compiled and installed (configure and make), any start/
# 	stop scripts and NAME anv VENDOR. The info is saved in
# 	/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/CFG
# 
cat << "END_OF_CFG" > CFG
URL="http://freshmeat.net/redir/bmon/36580/url_tgz/bmon-2.0.1.tar.gz"
PKG="bmon"
VER="2.0.1"
NAME="Portable bandwidth monitor and rate estimator"
VENDOR="Thomas Graf <tgraf@suug.ch>"
SRC="bmon-2.0.1"
ROOT="/var/opt/UNItools"
CONFIGURE="configure --prefix=$ROOT --mandir=$ROOT/share/man --bindir=$ROOT/bin --sbindir=$ROOT/bin"
BUILD="make"
INSTALL="make install"
INSTALL_MORE="/bin/sh install_more.sh"
MAKECLEAN="make distclean"
DELEFILES="*.bak"

# slut
END_OF_CFG
# 
#  3	Compile the package and create a temporary installation. If some
# 	of the applications needs to be created static then it *may* be
# 	required to set the env. var LDFLAGS=-static
#     
# export LDFLAGS=-static
# 
# 	If bmon is made with automake and configure then
# 
 	pkg_conbat -n ./CFG
# 
# 	will build and install it temporarely in /var/opt/UNItools (which
# 	will be moved during the installation). A script for testing will
# 	also be produced. Use '-n' to avoid prompting for the renaming of
# 	/var/opt/UNItools
# 	If bmon requires something else to compile, please correct the
# 	section that writes to CFG.
# 	The new files are then moved to bmon.2.0.1.install.tmp - which
# 	will be wiped first.
# 	Copy extra files with ''install_more'' which sould add the files
# 	to /var/opt/UNItools/ ...
# 
# 	If bmon requires a start/stop script, then it will have to be made
# 	some where else and installed with /var/opt/UNItools/bin/setup.sh
# 
# 	The successful output of pkg_conbat is a test-archive for testing
# 	bmon on a firewall.
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
# pkg_setup http://www.carisma.slowglass.com/~tgr/bmon/files/bmon-2.0.1.tar.gz 2.0.1 bmon
# 
