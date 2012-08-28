#!/bin/sh
# 
#
#                                     Fri Sep 18 11:35:32 CEST 2015
# Preample
# --------
# This script is the documentation for how postfix 3.0.2 was downloaded,
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
# All configuration files:	/var/opt/UNItools/etc/postfix
# All relevant documentation:	/var/opt/UNItools/docs/postfix.3.0.2
# 
# Un-comment out the relevant commands to build the package.
# 
# Installation receipt
# --------------------
# Change to the working directory created by pkg_setup:
# cd /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/postfix
# 
#  1	Download the package postfix, and read the package documentation,
# 	usually README and INSTALL.
# 
# wget -N http://mirror.netinch.com/pub/postfix/postfix-release/official/postfix-3.0.2.tar.gz
# 
# /bin/gtar xvzf postfix-3.0.2.tar.gz
# 
#  2	Change the values below so they describe how the package has
# 	to be compiled and installed (configure and make), any start/
# 	stop scripts and NAME anv VENDOR. The info is saved in
# 	/lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/CFG
# 
cat << "END_OF_CFG" > CFG
# Download URL, product name and version
URL="http://mirror.netinch.com/pub/postfix/postfix-release/official/postfix-3.0.2.tar.gz"
PKG="postfix"
VER="3.0.2"

# Description used internally
NAME="postfix"

# The creator/copyright holder
VENDOR="http://mirror.netinch.com/pub/postfix/postfix-release/official/postfix-3.0.2.tar.gz"

# Local source location
SRC="postfix-3.0.2"

# prefix for ''make install' Do not change
ROOT=/var/opt/UNItools

# Arguments to configure, build command and installation command
CONFIGURE=""
BUILD="make makefiles	install_root=/var/opt/UNItools/postfix meta_directory=/var/opt/UNItools/postfix/libexec/postfix \
				command_directory=/var/opt/UNItools/postfix/usr/sbin		\
				config_directory=/var/opt/UNItools/postfix/etc/postfix		\
				daemon_directory=/var/opt/UNItools/postfix/usr/libexec/postfix		\
				data_directory=/var/opt/UNItools/postfix/var/lib/postfix		\
				mailq_path=/var/opt/UNItools/postfix/usr/bin/mailq		\
				manpage_directory=/var/opt/UNItools/postfix/usr/local/man		\
				newaliases_path=/var/opt/UNItools/postfix/usr/bin/newaliases		\
				queue_directory=/var/opt/UNItools/postfix/var/spool/postfix		\
				sendmail_path=/var/opt/UNItools/postfix/usr/sbin/sendmail


mkdir -p /var/opt/UNItools/postfix/etc/postfix/ /var/opt/UNItools/postfix/var/spool/postfix /var/opt/UNItools/postfix/var/lib/postfix

"
INSTALL="make non-interactive-package install_root=/var/opt/UNItools/postfix; 
cat << EOF > /var/opt/UNItools/postfix/etc/main.cf
inet_interfaces = 127.0.0.1
mynetworks = 127.0.0.0/8
smtputf8_enable = no
EOF
"
# clean-up commands
MAKECLEAN="make distclean"
DELEFILES="*.bak"

# Script to add information not added by make install
INSTALL_MORE="/bin/sh install_more.sh"

# Prototype rc start/stop script (absolute path or relative to CFG)
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
#  3	Compile the package and create a temporary installation. If some
# 	of the applications needs to be created static then it *may* be
# 	required to set the env. var LDFLAGS=-static
#     
# export LDFLAGS=-static
# 
# 	If postfix is made with automake and configure then
# 
 	pkg_conbat -n ./CFG
# 
# 	will build and install it temporarely in /var/opt/UNItools (which
# 	will be moved during the installation). A script for testing will
# 	also be produced. Use '-n' to avoid prompting for the renaming of
# 	/var/opt/UNItools
# 	If postfix requires something else to compile, please correct the
# 	section that writes to CFG.
# 	The new files are then moved to postfix.3.0.2.install.tmp - which
# 	will be wiped first.
# 	Copy extra files with ''install_more'' which sould add the files
# 	to /var/opt/UNItools/ ...
# 
# 	If postfix requires a start/stop script, then it will have to be made
# 	some where else and installed with /var/opt/UNItools/bin/setup.sh
# 
# 	The successful output of pkg_conbat is a test-archive for testing
# 	postfix on a firewall.
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
# pkg_setup http://mirror.netinch.com/pub/postfix/postfix-release/official/postfix-3.0.2.tar.gz 3.0.2 postfix
# 
