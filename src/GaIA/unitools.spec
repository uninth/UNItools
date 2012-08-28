#
# Proto spec for UNItools
#
# $Header$
#
# See http://www.ibm.com/developerworks/library/l-rpm2/
#

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
%define version 1.0
%define release 26

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

# Her skal laves noget, så man kan lave en automatisk opdatering
# dvs. links og cron skal bevares ved opgradering, men laves ved
# ny-installation
# Det der sker i  setup.sh  er ikke så hysterisk at det ikke kan
# køres igen og igen (?)
# %pre 
# if [ "$1" = "1" ]; then
# 	# Perform tasks to prepare for the initial installation
# elif [ "$1" = "2" ]; then
# 	# Perform whatever maintenance must occur before the upgrade begins
# fi

%pre
NOW=`/bin/date +%Y-%m-%d`
# Just before the upgrade/install
if [ "$1" = "1" ]; then
	# Perform tasks to prepare for the initial installation
	# - is CP installed?
	# - is the version of migrate newer than the version of CP?
	:
elif [ "$1" = "2" ]; then
	# Perform whatever maintenance must occur before the upgrade begins
	if [ -f /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg ]; then
		/bin/cp /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg.${NOW}
	fi
	if [ -f /var/opt/UNItools/etc/edge_backup.cfg ]; then
		/bin/cp /var/opt/UNItools/etc/edge_backup.cfg /var/opt/UNItools/etc/edge_backup.cfg.${NOW}
	fi
fi

# post install script -- just before %files
%post
# Just after the upgrade/install
if [ "$1" = "1" ]; then
	# Perform tasks for for the initial installation
	/var/opt/UNItools/bin/setup.sh install
elif [ "$1" = "2" ]; then
	# Perform whatever maintenance must occur after the upgrade has ended
	if [ -f /var/opt/UNItools/etc/edge_backup.cfg.${NOW} ]; then
		/bin/mv /var/opt/UNItools/etc/edge_backup.cfg.${NOW} /var/opt/UNItools/etc/edge_backup.cfg
	fi
	if [ -f /var/opt/UNItools/etc/edge_backup.cfg.${NOW} ]; then
		/bin/mv /var/opt/UNItools/etc/edge_backup.cfg.${NOW} /var/opt/UNItools/etc/edge_backup.cfg
	fi
fi

# If the first argument to %preun and %postun is 1, the action is an upgrade.
# If the first argument to %preun and %postun is 0, the action is uninstallation.

# pre uninstall script
%preun
# Just after the upgrade/install
if [ "$1" = "1" ]; then
	# upgrade - do nothing here
	:
elif [ "$1" = "0" ]; then
	# uninstallation
	echo "%preun: \$1 = $1 - unistallation"
	echo "removing /etc/cron.d/UNItools_backup"
	/bin/rm -f /etc/cron.d/UNItools_backup
	echo "restarting crond .. "
	/etc/init.d/crond restart
	echo "You may have to remove everything below /var/opt/UNItools"
	echo "and remove unwanted hosts in /etc/hosts with clish"
	echo "also, please remove/edit keys in $HOME/.ssh/authorized_keys" 
fi

# All files below here - special care regarding upgrade for the config files
%files
%config /var/opt/UNItools/etc/edge_backup.cfg
%config /var/opt/UNItools/conf/smtpclient.SH
%config /var/opt/UNItools/fwbu/etc/UNIcpfwbu.cfg
/var/opt/UNItools
