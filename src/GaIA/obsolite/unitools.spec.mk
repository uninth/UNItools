#! /bin/bash
#
# $Header$
#

VERSION=$1
RELEASE=$2

# VERSION=1.0
# RELEASE=1

cat << EOF 

AutoReqProv: no

# for compatibility with old md5 digest
# %global _binary_filedigest_algorithm 1
# %global _source_filedigest_algorithm 1

%define defaultbuildroot /
# Do not try autogenerate prereq/conflicts/obsoletes and check files
%undefine __check_files
%undefine __find_prereq
%undefine __find_conflicts
%undefine __find_obsoletes
# Be sure buildpolicy set to do nothing
%define __spec_install_post %{nil}
# Something that need for rpm-4.1
%define _missing_doc_files_terminate_build 0

%define name    UNItools
%define version ${VERSION}
%define release ${RELEASE}

Summary: The Check Point Firewall administrators toolbox
Name: %{name}
Version: %{version}
Release: %{release}
License: GPL
Group: root
Packager: Niels Thomas Haugaard, nth@i2.dk
Vendor: i2 - Intelligent Infrastructure, the Danish Technical University
%description
Tools for simplified administration of Check Point firewalls based on GAiA

%prep
test -d /lan/ssi/shared/software/internal/UNItools/src/GaIA/UNItools_buildroot/var/opt/ || {
	mkdir -p /lan/ssi/shared/software/internal/UNItools/src/GaIA/UNItools_buildroot/var/opt
}
rsync -avzH /var/opt/UNItools /lan/ssi/shared/software/internal/UNItools/src/GaIA/UNItools_buildroot/var/opt/
ln -s /lan/ssi/shared/software/internal/UNItools/src/GaIA/UNItools_buildroot /tmp/UNItools_buildroot

%clean
rm /tmp/UNItools_buildroot

# post install script -- just before %files
%post

echo "Now configure the package with"
echo "/var/opt/UNItools/bin/setup.sh"
echo "Uninstall the package by removing it with rpm -e --nodeps UNItools-${VERSION}-${RELEASE}"

# pre uninstall script
%preun
echo "removing /etc/cron.d/UNItools_backup"
/bin/rm -f /etc/cron.d/UNItools_backup
echo "restarting crond .. "
/etc/init.d/crond restart
echo "You may have to remove everything below /var/opt/UNItools"

# All files below here - special care regarding upgrade for the config files
%files
%config /var/opt/UNItools/etc/edge_backup.cfg
%config /var/opt/UNItools/conf/smtpclient.SH
%config /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg
/var/opt/UNItools
EOF
