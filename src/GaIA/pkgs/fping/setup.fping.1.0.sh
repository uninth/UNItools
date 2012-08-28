# #!/bin/sh
# ##
#                                      Mon Mar 10 23:54:51 CET 2014
# 
# This document is a description for how version 1.0 of fping has
# to be compiled for use on GaIA, the Check Point security appliance.
# 
# It is a shell script, executing it will produce the version which
# is part of UNItools.pkg
# 
# All programs, README etc. ends up below /var/opt/UNItools. No man
# pages, include files or other stuff.
# 
# All binary programs:		/var/opt/UNItools/bin
# All configuration files:	/var/opt/UNItools/etc/fping
# All relevant documentation:	/var/opt/UNItools/docs/fping.1.0
# 
# This is *not* a Linux PKG package; but UNItools is. This is the
# pre-requisite for the final package and a note on how it was made.
# 
# Installation receipt for fping, version :
# 
# 1  Download the package fping to /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/fping
# Read the package documentation - usually README and INSTALL.
# 
# wget -N http://fping.sourceforge.net/download/fping.tar.gz
# 
# /bin/gtar xvzf fping.tar.gz
# 
# 2  Change the values below so they describe how the package has
# to be compiled and installed (configure and make), any start/
# stop scripts and NAME anv VENDOR. The info is saved in
# /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/CFG
# 
cat << "END_OF_CFG" > CFG
# The following is sourced by /bin/sh -- you have been warned!
# If PKG_STATUS != OK then it will not be installed 
PKG_STATUS=""

# Toolbox category
# SPM:	System Performance Monitors
# NPM:	Network Performance Monitors
# NT:	Network Tools
# SP:	Special Purpose Monitors
# GT:	General Tools 
TOOLBOX_CAT="SPM"

URL="http://fping.sourceforge.net/download/fping.tar.gz"
PKG="fping"
VER="fping-2.4b2_to-ipv6"
# Description -- URL added at end
NAME="fping"
# Company or peron
VENDOR="David Papp"
# Local source placed here
SRC="fping-2.4b2_to-ipv6"
# Top prefix for ''make install'
ROOT=/var/opt/UNItools
# Arguments to configure, build command and installation command
CONFIGURE="configure --prefix=$ROOT --mandir=$ROOT/share/man --bindir=$ROOT/bin --sbindir=$ROOT/bin"
BUILD="make"
INSTALL="make install"
# clean-up commands
MAKECLEAN="make distclean"
DELEFILES="*.bak"
# Script to add information not added by make install
INSTALL_MORE="/bin/sh install_more.sh"
#  Prototype rc start/stop script (absolute path or relative to CFG)
RCPROTO=""
# RCSTART="S88unizlib"
RCSTART=""
# RCSTOP="S88unizlib"
RCSTOP=""
# Run level /etc/rcX.d. Network: 3, hernel S, user space (databases etc): 3
# netværksdaemoner: normalt 2, kerneting normalt S, databaser mv normalt 3
# RCSTARTDIRS="3"
RCSTARTDIRS=""
# Same for stop scripts: S, 0 and 1 - multible doesn't make any difference
# RCSTOPDIRS="S 0 1"
RCSTOPDIRS=""
END_OF_CFG
# 
#  3  Compile the package and create a temporary installation. If some
#     of the applications needs to be created static then it *may* be
# 	required to set the env. var LDFLAGS=-static
#     
# export LDFLAGS=-static
# 
# 	If the package is using automake and configure then
# 
pkg_fake_install.sh -n ./CFG
# 
# 	will configure, compile and install the package. This will require
# 	a temporary renaming of /var/opt/UNItools. The '-n' flag implies
# 	do not prompt and assumes no-one is using anything from UNItools
# 	on the compile host rhes3.ssi.i2.dk.
# 	If fping requires something else to compile, please correct the
# 	section that writes to CFG.
# 
# 	fping is moved to fping.1.0.install.tmp, after
# 	compilation and installation. The content of the directory is
# 	removed each time pkg_fake_install.sh is executed.
# 
# 	The documentation (if any) from fping is converted to html, txt and
# 	pdf and saved in docs/fping.1.0. You are encuraged to check
# 	if the package contains othe document which should go there as well.
# 	Use the script more_install.sh for that.
# 
#  5  Do dependency check, specially useful for shared libs etc.
# 
pkg_mkrpm_dep.sh ./CFG depend
#  	
# 	If fping requires a start/stop script, then it will have to be made
# 	some where else and installed with /var/opt/UNItools/bin/setup.sh
# 
#	6  Add additional documents which doesn't get installed with make install.
#     Edit the script in INSTALL_MORE and ensure it is executed as part of
#     the install procedure. The installed documents should be copy'ed to
# 	fping.1.0.install.tmp.
# 
# 	Feel free to modify the template script install_more.sh next to
# 	this document. You can also add the commands below (this is a script
# 	too)
# 
#  7  Make some documentation with the command
# 
pkg_mkdoc.sh ./CFG
# 
#  8  Create a zipped tar archive with relative paths of the package
# 
# 	pkg_build.sh ./CFG
# 
#  9	Install the package on a firewall and test it. 
#  
# 10	If everything os OK then add the package to /var/opt/UNItools with
#     the command
# 
# 	pkg_install.sh ./CFG
# 
#     which will also add stuff to our internal wiki etc.
# 
# 11	Finally clean up with
# 
# 	pkg_clean.sh	./CFG
# 
# If /var/opt/UNItools gets poluted with unwanted stuff, you may do a clean
# install of everything with
# 
# 	pkg_do_it_all_for_all_known_packages
# 
# The script doesn't execute /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/fping/setup.fping.1.0.sh directly, rather it executes
# .stable - a link which points to the latest stable version of fping.
# 
# 12
# 	Finally make a new Linux PKG version of UNItools
# 
