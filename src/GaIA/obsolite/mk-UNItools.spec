#!/bin/bash

tmpfile=/tmp/$$

#
cat << 'EOF' > ./UNItools-R77.10.GaIA.spec

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
%define version R77.10.GaIA

Summary: i2 tool collection
Name: %{name}
Version: %{version}
Release: 1.0
License: GPL
Group: root
Packager: Niels Thomas Haugaard, nth@i2.dk

%description
i2 tool collection for version for GaIA, R76 and R77*

%prep
ln -s /san/data/shared/software/internal/UNItools/src/GaIA/UNItools_rootdir /tmp/rpmerizor_buildroot

%clean
rm /tmp/rpmerizor_buildroot

# post install script -- just before %files
%post

echo "Now configure the package with"
echo "/var/opt/UNItools/bin/setup.sh"
echo "Uninstall the package by removing it with rpm -e --nodeps ... "

# pre uninstall script
%preun
echo "removing /etc/cron.d/UNItools_backup"
/bin/rn -f /etc/cron.d/UNItools_backup
echo "restarting crond .. "
/etc/init.d/crond restart
echo "You may have to remove everything below /var/opt/UNItools"

# All files below here - special care regarding upgrade for the config files
%files
/var/opt/UNItools
%config /var/opt/UNItools/etc/edge_backup.cfg
%config /var/opt/UNItools/conf/smtpclient.SH
%config /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg
EOF
