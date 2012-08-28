#!/bin/bash
#
# $Header: /lan/ssi/shared/software/internal/UNItools/src/GaIA/pkgs/setup/setup-1.0/RCS/setup.sh,v 1.1 2014/05/13 21:45:47 root Exp $
#

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

if [ -f /etc/profile.d/CP.sh ]; then 
	.  /etc/profile.d/CP.sh
fi

if [ -f /etc/profile.d/CPshell.sh ]; then 
	.  /etc/profile.d/CPshell.sh
fi      

if [ "x$SHLVL" != "x1" ]; then # We're not a login shell
	for i in /etc/profile.d/*.sh; do
		if [ -x $i ]; then 
			. $i    
		fi      
	done    
fi

echo "Wellcome to UNItools configuration for GaIA R77.10"
echo "Stop now if you dont like changes"

sleep 5

echo "changing admin user shell and inactivity-timeout"
echo "user = admin shell = /bin/bash inactivity-timeout 720"

clish -sc "set user admin shell /bin/bash"
clish -sc "set inactivity-timeout 720"

echo "clish command done"

echo  "enabeling admin scp in /etc/scpusers ... "
echo "admin" > /etc/scpusers

/bin/chown root:root /etc/scpusers
/bin/chmod 444 /etc/scpusers

echo "done"

echo "configuring .bash_profile for the admin user ... "
/bin/cp /var/opt/UNItools/conf/.bash_profile /home/admin

echo "Setting up ssh keys for user admin (aka root, uid 0) ... "

if [ ! -f "$HOME/.ssh/authorized_keys" ]; then
echo "creating default dsa, rsa and sha1 keys ... "
echo "" | ssh-keygen -t dsa 2>/dev/null
echo "" | ssh-keygen -t rsa 2>/dev/null
echo "" | ssh-keygen -t rsa1 2>/dev/null
echo "adding our key to authorized_keys ... "
cat << EOF > /home/admin/.ssh/authorized_keys
ssh-dss AAAAB3NzaC1kc3MAAACBAKUq/J8WuZgxZ++M4H7LplAd2xhKLpSHeL733LHpd6At2Yb9GgT7vfQYhqHCCMz8X1W3rt//BI0gm+8Dm7+Lkkh/4MY9l2LiQzzXOb1SzyQxOw90O6VyysuWnOkot+oxY2VD7305R3LLHgUy4ZvekyFcuh0hSPHEeL8U2rziLzSJAAAAFQCJ6NgOjgBWO6xoULsK5kTrPlGXGwAAAIBD9FFz5+dPhioq2trpEhDfA17WxqTU5P+udvLsvO+yfkoPSt1OuSFgP2p8sXBigqBKkte8fqjGsMRW1AwEo6UumDfiiTJP5tecp9EoVQi1SvlNF+4G0zWokVumeuFlfo7aES5eu9lFbjlSj3WOWyG/AdMBfIU30m02gXlFhXnjxAAAAIAMKYAU/QVAkE6hYoZMcXU1lNocFDwnq2olz0kr2Aq6biXGxE/tgkpfq35fJD5xteaxVWNuv0y+w8+Ny5l5D6NTHAC+Rro0W8riTforrWjVYwdNCZCguf/CwWe1M/RtjbHh5WnCDLRwwG16k/zlJfWuewwbxwfsvh5uaK1ZCVg1fw== uninth@caliban.ssi.uni-c.dk
EOF
else
echo "existing ssh configuration not changed"
fi

chmod -R 700 $HOME/.ssh $HOME/.ssh/*

grep -q 130.225.245.210 /etc/hosts
case $? in
	0) echo "found 130.225.245.210 in /etc/hosts"
	;;
	*) clish -sc "add host name fwgui ipv4-address 130.225.245.210"
	   echo "added 130.225.245.210 to /etc/hosts"
	;;
esac

echo "done. ssh access w/o password granted from SSI"

echo "Enabeling scheduled backup of Check Point firewall-1 ... "

if [ -d /etc/cron.d ]; then
	cat << EOF > /etc/cron.d/UNItools_backup
# periodic firewall backup
40 7 * * * root /var/opt/UNItools/fwbu/bin/UNIcpfwbu.sh
EOF
	chmod 644 /etc/cron.d/UNItools_backup

	/etc/init.d/crond restart
else
	echo "no /etc/cron.d please fix"
fi
            
echo "setting up softlinks ... "
(
	cd /var/opt/UNItools/bin
	for FILE in tar gunzip gzip bash domainname hostname md5sum
	do
		/bin/rm -f ${FILE}
		ln -s `type ${FILE} | awk '{ print $NF }'` ${FILE}
		echo "${FILE} ... "
	done
)

find /var/opt/UNItools/bin -type l -exec ls -l {} \; 

echo "undo by un-install UNItools and remove admin user auth. keys"
echo "use clish to change admin users SHELL and time out"
echo "remove /etc/hosts entries with clish"
